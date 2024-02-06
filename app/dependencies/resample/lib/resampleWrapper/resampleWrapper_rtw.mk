###########################################################################
## Makefile generated for component 'resampleWrapper'. 
## 
## Makefile     : resampleWrapper_rtw.mk
## Generated on : Sun Feb 04 10:31:18 2024
## Final product: ./resampleWrapper.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = resampleWrapper
MAKEFILE                  = resampleWrapper_rtw.mk
MATLAB_ROOT               = /usr/local/MATLAB/R2023b
MATLAB_BIN                = /usr/local/MATLAB/R2023b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
START_DIR                 = /home/abhinav/abhi/college/sem6/BTP/BTP_App/entry\ points
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv
MODELLIB                  = resampleWrapper.a

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ | gmake (64-bit Linux)
# Supported Version(s):    
# ToolchainInfo Version:   2023b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS         = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX     = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS     = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC = gcc

# Linker: GNU Linker
LD = g++

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/glnxa64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O3 -fno-loop-optimize -fno-aggressive-loop-optimizations
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./resampleWrapper.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/resampleWrapper -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=resampleWrapper

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_data.cpp $(START_DIR)/codegen/lib/resampleWrapper/rt_nonfinite.cpp $(START_DIR)/codegen/lib/resampleWrapper/rtGetNaN.cpp $(START_DIR)/codegen/lib/resampleWrapper/rtGetInf.cpp $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_initialize.cpp $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_terminate.cpp $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper.cpp $(START_DIR)/codegen/lib/resampleWrapper/uniformResample.cpp $(START_DIR)/codegen/lib/resampleWrapper/ipermute.cpp $(START_DIR)/codegen/lib/resampleWrapper/assertValidSizeArg.cpp $(START_DIR)/codegen/lib/resampleWrapper/firls.cpp $(START_DIR)/codegen/lib/resampleWrapper/validateattributes.cpp $(START_DIR)/codegen/lib/resampleWrapper/minOrMax.cpp $(START_DIR)/codegen/lib/resampleWrapper/any1.cpp $(START_DIR)/codegen/lib/resampleWrapper/indexShapeCheck.cpp $(START_DIR)/codegen/lib/resampleWrapper/xnrm2.cpp $(START_DIR)/codegen/lib/resampleWrapper/kaiser.cpp $(START_DIR)/codegen/lib/resampleWrapper/upfirdnCoreImpl.cpp $(START_DIR)/codegen/lib/resampleWrapper/eml_int_forloop_overflow_check.cpp $(START_DIR)/codegen/lib/resampleWrapper/mldivide.cpp $(START_DIR)/codegen/lib/resampleWrapper/xgeqp3.cpp $(START_DIR)/codegen/lib/resampleWrapper/xzlarf.cpp $(START_DIR)/codegen/lib/resampleWrapper/gammaln.cpp $(START_DIR)/codegen/lib/resampleWrapper/cmlri.cpp $(START_DIR)/codegen/lib/resampleWrapper/casyi.cpp $(START_DIR)/codegen/lib/resampleWrapper/uniformParserNBetaAndDesignFilter.cpp $(START_DIR)/codegen/lib/resampleWrapper/div.cpp $(START_DIR)/codegen/lib/resampleWrapper/eml_mtimes_helper.cpp $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_rtwutil.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = resampleWrapper_data.o rt_nonfinite.o rtGetNaN.o rtGetInf.o resampleWrapper_initialize.o resampleWrapper_terminate.o resampleWrapper.o uniformResample.o ipermute.o assertValidSizeArg.o firls.o validateattributes.o minOrMax.o any1.o indexShapeCheck.o xnrm2.o kaiser.o upfirdnCoreImpl.o eml_int_forloop_overflow_check.o mldivide.o xgeqp3.o xzlarf.o gammaln.o cmlri.o casyi.o uniformParserNBetaAndDesignFilter.o div.o eml_mtimes_helper.o resampleWrapper_rtwutil.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS =  -L"$(MATLAB_ROOT)/sys/os/glnxa64" -lm -lstdc++ -liomp5

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_OPTS = -fopenmp
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_OPTS = -fopenmp
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/resampleWrapper/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/resampleWrapper/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/resampleWrapper/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/resampleWrapper/%.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/resampleWrapper/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/resampleWrapper/%.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/resampleWrapper/%.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


resampleWrapper_data.o : $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_data.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/codegen/lib/resampleWrapper/rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/codegen/lib/resampleWrapper/rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/codegen/lib/resampleWrapper/rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


resampleWrapper_initialize.o : $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_initialize.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


resampleWrapper_terminate.o : $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_terminate.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


resampleWrapper.o : $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


uniformResample.o : $(START_DIR)/codegen/lib/resampleWrapper/uniformResample.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


ipermute.o : $(START_DIR)/codegen/lib/resampleWrapper/ipermute.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


assertValidSizeArg.o : $(START_DIR)/codegen/lib/resampleWrapper/assertValidSizeArg.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


firls.o : $(START_DIR)/codegen/lib/resampleWrapper/firls.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


validateattributes.o : $(START_DIR)/codegen/lib/resampleWrapper/validateattributes.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


minOrMax.o : $(START_DIR)/codegen/lib/resampleWrapper/minOrMax.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


any1.o : $(START_DIR)/codegen/lib/resampleWrapper/any1.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


indexShapeCheck.o : $(START_DIR)/codegen/lib/resampleWrapper/indexShapeCheck.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


xnrm2.o : $(START_DIR)/codegen/lib/resampleWrapper/xnrm2.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


kaiser.o : $(START_DIR)/codegen/lib/resampleWrapper/kaiser.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


upfirdnCoreImpl.o : $(START_DIR)/codegen/lib/resampleWrapper/upfirdnCoreImpl.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


eml_int_forloop_overflow_check.o : $(START_DIR)/codegen/lib/resampleWrapper/eml_int_forloop_overflow_check.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


mldivide.o : $(START_DIR)/codegen/lib/resampleWrapper/mldivide.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


xgeqp3.o : $(START_DIR)/codegen/lib/resampleWrapper/xgeqp3.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


xzlarf.o : $(START_DIR)/codegen/lib/resampleWrapper/xzlarf.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


gammaln.o : $(START_DIR)/codegen/lib/resampleWrapper/gammaln.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


cmlri.o : $(START_DIR)/codegen/lib/resampleWrapper/cmlri.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


casyi.o : $(START_DIR)/codegen/lib/resampleWrapper/casyi.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


uniformParserNBetaAndDesignFilter.o : $(START_DIR)/codegen/lib/resampleWrapper/uniformParserNBetaAndDesignFilter.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


div.o : $(START_DIR)/codegen/lib/resampleWrapper/div.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


eml_mtimes_helper.o : $(START_DIR)/codegen/lib/resampleWrapper/eml_mtimes_helper.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


resampleWrapper_rtwutil.o : $(START_DIR)/codegen/lib/resampleWrapper/resampleWrapper_rtwutil.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


