import numpy as np


def formant_CGDZP(wave, fs, frameSize=30, frameShift=10):
    # if frameShift is None:
    #     frameShift = 10
    # if frameSize is None:
    #     frameSize = 30
    
    numFormants = 5
    numFormatsFinal = numFormants
    frameSize = int(fs / 1000 * frameSize)
    frameShift = int(fs / 1000 * frameShift)
    fsLR = 2048  # lower resolution
    viewRange = round(fsLR / 3.2)
    R = 1.12
    Rfix = R
    maxFormantDelta = 250  # discontinuity constraint(in Hz.) in formant tracks 

    n = np.arange(0, frameSize - 1)  # zeroPhase data has length of N-1

    ScalingFreqAxis = np.arange(0.5, 1.5, 1 / (viewRange - 1))
    ScalingFreqAxis = ScalingFreqAxis - 0.25
    CepsSmoothSelectPercent = 3
    SelectTimeIndex = round(CepsSmoothSelectPercent * fsLR / 2 / 100)

    SIZEwave = len(wave)
    numFrames = int(np.floor((SIZEwave - frameSize) / frameShift))

    t_analysis = np.zeros(numFrames)
    blackWin = np.blackman(frameSize)

    formantPeaks = []
    for kk in range(numFrames):
        speechData = wave[kk * frameShift: kk * frameShift + frameSize]
        windowedData = speechData * blackWin
        
        zeroPhaseData = np.real(np.fft.ifft(np.abs(np.fft.fft(np.diff(windowedData)))))  # obtain zero-phase version
        
        numPeaks = 0
        R = Rfix
        while numPeaks != numFormants and R > 1.01 and R < 1.25:
            # Chirp z-transform calculation using fft,... multiplication with an exponential function is sufficient
            exponentialEnvelope = np.exp(np.log(1 / R) * n)  # this is needed for computation of z-transform using fft
            fourierTrans = np.fft.fft(zeroPhaseData * exponentialEnvelope, fsLR)
            angFFT = np.angle(fourierTrans[:viewRange])
            chirpGroupDelay = -np.diff(angFFT)
            
            peakIndex = formantPeakPick(chirpGroupDelay, 1)
            numPeaks = len(peakIndex)
            if numPeaks > numFormants and R >= Rfix:
                R += 0.01
                peakIndex = peakIndex[:numFormants]
            elif numPeaks < numFormants and R <= Rfix:
                R -= 0.01
                peakIndex += [0] * (numFormants - numPeaks)
            else:
                break
        
        if numPeaks > numFormants:
            peakIndex = peakIndex[:numFormants]
        elif numPeaks < numFormants:
            peakIndex += [0] * (numFormants - len(peakIndex))
        
        formantPeaks.append(peakIndex)
        t_analysis[kk] = round(((kk * frameShift + kk * frameShift + frameSize) / 2) / fs)
    formantPeaks = np.round(np.array(formantPeaks) * fs / fsLR)

    if True:  # filtering
        # form a matrix of distance cost
        formantPeaksCost = formantPeaks * 0
        for kk in range(2, numFrames - 2):
            prePrePeaks = formantPeaks[kk - 2, :]
            postPostPeaks = formantPeaks[kk + 2, :]
            prePeaks = formantPeaks[kk - 1, :]
            postPeaks = formantPeaks[kk + 1, :]
            currentPeaks = formantPeaks[kk, :]
            currentPeaksCost = currentPeaks * 0  # cost will correspond to average distance from closest match to neighbours
            for mm in range(numFormants):
                if currentPeaks[mm] == 0:
                    currentPeaksCost[mm] = fs / 2
                else:
                    # search for closest matches
                    distanceArrayPre = sorted(abs(prePeaks - currentPeaks[mm]))
                    distanceArrayPost = sorted(abs(postPeaks - currentPeaks[mm]))
                    distanceArrayPrePre = sorted(abs(prePrePeaks - currentPeaks[mm]))
                    distanceArrayPostPost = sorted(abs(postPostPeaks - currentPeaks[mm]))
                    allDistances = [(distanceArrayPre[0] + distanceArrayPost[0]) / 2, distanceArrayPre[0], distanceArrayPost[0]]
                    allDistances2 = [(distanceArrayPrePre[0] + distanceArrayPostPost[0]) / 2, distanceArrayPrePre[0], distanceArrayPostPost[0]]
                    currentPeaksCost[mm] = min(allDistances + allDistances2)
            formantPeaksCost[kk, :] = currentPeaksCost
        for kk in range(numFrames):
            for mm in range(numFormants):
                if formantPeaksCost[kk, mm] > maxFormantDelta:
                    formantPeaks[kk, mm] = 0
    if True:  # replace possible continuation values instead of zero values
        for kk in range(1, numFrames - 1):
            currentPeaks = formantPeaks[kk, :]
            index = [i for i, val in enumerate(currentPeaks) if val != 0]  # finds non-zero elements
            nonZeroFormants = currentPeaks[index]
            numNonZeroFormants = len(index)
            numZeroFormants = numFormants - numNonZeroFormants
            if numNonZeroFormants < numFormants and index:
                possibleValues = sorted([val for val in [formantPeaks[kk - 1, :], formantPeaks[kk + 1, :]]])
                possibleValues = [val for sublist in possibleValues for val in sublist if val != 0]  # discard zero entries
                possibleCandidates = []
                for mm in range(len(possibleValues)):
                    distanceArray = sorted(abs(nonZeroFormants - possibleValues[mm]))
                    if not distanceArray or distanceArray[0] > maxFormantDelta:  # this possible value not found in the current vector
                        possibleCandidates.append(possibleValues[mm])
                # choose among possible candidates
                lenPossibleCandidates = len(possibleCandidates)
                if lenPossibleCandidates <= numZeroFormants:
                    currentPeaks = sorted(nonZeroFormants + possibleCandidates + [0] * (numZeroFormants - lenPossibleCandidates))
                elif numZeroFormants == 1:  # the most common case
                    index = sorted(range(len(possibleCandidates)), key=lambda x: possibleCandidates[x + 1] - possibleCandidates[x])
                    currentPeaks = sorted(nonZeroFormants + [possibleCandidates[index[0]]] + [0])
                elif numZeroFormants < lenPossibleCandidates:
                    possibleCandidates = possibleCandidates[:numZeroFormants]
                    currentPeaks = sorted(nonZeroFormants + possibleCandidates)
                formantPeaks[kk, :] = currentPeaks

def formantPeakPick(diffPhase, minPeakDist):
    lendiffPhase = len(diffPhase)
    peakIndex = []

    for kk in range(6, lendiffPhase - 6):
        if (diffPhase[kk] >= diffPhase[kk - 1] and diffPhase[kk] >= diffPhase[kk + 1]) and \
           (diffPhase[kk] >= diffPhase[kk - 2] and diffPhase[kk] >= diffPhase[kk + 2]) and \
           (diffPhase[kk] > diffPhase[kk - 3] and diffPhase[kk] > diffPhase[kk + 3]) and \
           (diffPhase[kk] > diffPhase[kk - 4] and diffPhase[kk] > diffPhase[kk + 4]) and \
           (diffPhase[kk] > diffPhase[kk - 5] and diffPhase[kk] > diffPhase[kk + 5]):
            peakIndex.append(kk)

    lenPeakInd = len(peakIndex)
    kk = 2
    while kk <= lenPeakInd:
        if peakIndex[kk] - peakIndex[kk - 1] < minPeakDist:
            peakIndex[kk] = round((peakIndex[kk] * diffPhase[kk] + peakIndex[kk - 1] * diffPhase[kk - 1]) /
                                  (diffPhase[kk] + diffPhase[kk - 1]))
            peakIndex = peakIndex[:kk - 1] + [peakIndex[kk]] + peakIndex[kk:lenPeakInd]
            kk -= 1
            lenPeakInd -= 1
        kk += 1

    return peakIndex
