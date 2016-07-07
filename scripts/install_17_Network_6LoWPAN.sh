#!/bin/bash

#
#  Install script for Fixpoint Mathematical Library 
#  URL: http://code.google.com/p/fixpointlib/
#
#  Initial Script written by Gregor Rebel 2010-2012.
# 
#  Published under GNU Lesser General Public License
#  Check LEGAL.txt for details.
#
# Tested successfully on:
# openSuSE 12.1 x86
# XUbuntu 11.10 x64

source scripts/installFuncs.sh
checkUserRoot "$1" "$2"

# Note: Must change fields below!
RANK="450"
EXTENSION_NAME="network_6lowpan"

StartPath="`pwd`"
INSTALLPATH="${RANK}_${EXTENSION_NAME}"
dir "$INSTALLPATH"
cd "$INSTALLPATH"

#{ IMPLEMENT YOUR INSTALL SCRIPT BELOW -----------------------------------------------

#{ look for newest versions on download pages
NewestDownloads="../${0}_downloads"
if [ "$1" == "FINDNEWEST" ] || [ ! -e "$NewestDownloads" ]; then #{ find newest downloads
  # echo -n "$0: looking for new GCC... "
  # updateNewest GCC https://launchpad.net/gcc-arm-embedded/+download 'gcc-arm-none-eabi-.+-linux\.tar\.bz2' $NewestDownloads
  if [ "$return" != "" ]; then
    # prepare folder for new version
    rm -Rf *
  fi
fi #}
if [ -e "$NewestDownloads" ]; then
  source $NewestDownloads
fi
# if [ "$GCC_URL" == "" ] || [ "$GCC_File" == "" ]; then #{ check if at least one version has been found 
#   echo "$0 - ERROR: Cannot find newest GCC version!"
#   exit 10
# fi #}
#}look for newest versions

if [ ! -e OK.Docs ];    then    #{ (download documentation)

  Get_Fails=""
  
  # download doc-file + move to Documentation/ + create symbolic link into Documentation/ right here 
  # File="STM32F10x_Standard_Peripherals_Library.html"
  # getFile http://www.mikrocontroller.net/articles/ STM32F10x_Standard_Peripherals_Library $File
  # addDocumentationFile $File STM
  
  if [ "$Get_Fails" == "" ]; then #{ check get() inside scripts/installFuncs.sh 
    touch OK.Docs
  else
    echo "$0 - ERROR: missing files: $Get_Fails"
  fi #}
fi #}
if [ ! -e OK.Install ]; then    #{ (download + install third party software)
  if [ ! -e OK.Packages ]; then #{ install packages
    FailedInstalls=""
    
    #installPackageSafe "which autoreconf" autoreconf
    
    if [ "$FailedInstalls" == "" ]; then
      touch OK.Packages
    else
      echo "$0 - ERROR: Cannot install required software packages: $FailedInstalls"
      exit 10
    fi
  fi #}
  if [ -e OK.Packages ];   then #{ install software
    echo "installing in $INSTALLPATH ..."
    InstallDir=`pwd`
    
    # getFile http://www.st.com/internet/com/SOFTWARE_RESOURCES/SW_COMPONENT/FIRMWARE/ stm32_i2c_cpal.zip stm32_i2c_cpal.zip
    # unZIP "UNKNOWN" stm32_i2c_cpal.zip
    
    #if [ -e "SOME_FILE" ]; then
      echo "" >OK.Install
    #fi
  else
    echo "$0 - ERROR: Packages were not installed correctly!"
  fi #}OK.Packages
fi #} [ ! -e OK.Install ]; then
if [   -e OK.Install ]; then    #{ create makefiles and activate scripts

  Name="${INSTALLPATH}"  
  createExtensionMakefileHead ${Name}      #{ (create makefile)
  cat <<END_OF_MAKEFILE >>$ExtensionMakeFile # variable set by createExtensionMakefileHead() 

# additional constant defines
#COMPILE_OPTS += -D

# additional directories to search for header files
INCLUDE_DIRS += -I ttc-lib/network

# additional directories to search for C-Sources
vpath %.c ttc-lib/network

# additional object files to be compiled
MAIN_OBJS += 6lowpan_mac_csma.o 6lowpan_mac_mac.o 6lowpan_mac_nullrdc.o \
             6lowpan_rime_rimeaddr.o 6lowpan_net_netstack.o 6lowpan_adapt_random.o \
             6lowpan_net_packetbuf.o 6lowpan_net_queuebuf.o 6lowpan_radio_serialradio.o \
             6lowpan_adapt_memb.o 6lowpan_adapt_list.o 6lowpan_adapt_ctimer.o \
             6lowpan_mac_nullmac.o 6lowpan_adapt_rtimer.o 6lowpan_mac_framer_802154.o \
             6lowpan_mac_frame802154.o

ifdef DISABLED_FOO
MAIN_OBJS +=  6lowpan_net_neighbor_attr.o 6lowpan_net_neighbor_info.o \
              6lowpan_net_sicslowpan.o 6lowpan_net_tcpip.o 6lowpan_net_uip_arp.o \
              6lowpan_net_uip.o 6lowpan_net_uip_debug.o 6lowpan_net_uip_ds6.o \
              6lowpan_net_uip_fw.o 6lowpan_net_uip_icmp6.o 6lowpan_net_uip_nd6.o \
              6lowpan_net_uip_packetqueue.o 6lowpan_net_uip_split.o 6lowpan_adapt_watchdog.o \
              6lowpan_adapt_etimer.o
endif

# 6lowpan_radio_nullradio.o 6lowpan_mac_framer_nullmac.o
# 6lowpan_adapt_compower.o 6lowpan_adapt_energest.o  \
# 6lowpan_adapt_leds.o 6lowpan_mac_contikimac.o
# 6lowpan_rime_rime.o 6lowpan_rime_rimestats.o 6lowpan_mac_nullrdc_framer.o 

MAIN_OBJS += ttc_network_driver_6lowpan.o

END_OF_MAKEFILE
  createExtensionMakefileTail ${Name} #}
  createActivateScriptHead $Name ../extensions/ "$0 2" "802.15.4 & 6LoWPAN Communications Stacks $0" #{ (create activate script)
  cat <<END_OF_ACTIVATE >>$ActivateScriptFile
# available variables (-> scripts/installFuncs.sh:createActivateScriptHead())
#
# Paths to certain directories in current project folder
#   \$Dir_Extensions        -> extensions/
#   \$Dir_ExtensionsLocal   -> extensions.local/
#   \$Dir_ExtensionsActive  -> extensions.active/
#   \$Dir_Additionals       -> additionals/
#   \$Dir_Configs           -> configs/

# ACTIVATE_SECTION_A remove activated variants of same type
# rm 2>/dev/null \$Dir_ExtensionsActive/*${INSTALLPATH}_*

#Architecture=\`ls -f extensions.active/*radio*\`

#ifdef TTC_NETWORK_6LOWPAN
	#if [ "\$Architecture" != "" ]; then
	#  activate.500_ttc_network.sh QUIET \"\$0\"
	#  activate.500_ttc_timer.sh QUIET \"\$0\"
	#  activate.500_ttc_memory.sh QUIET \"\$0\"
	#  activate.500_ttc_list.sh QUIET \"\$0\"
	#  activate.500_ttc_task.sh QUIET \"\$0\"
	#  activate.500_ttc_random.sh QUIET \"\$0\"
	#  activate.500_ttc_mutex.sh QUIET \"\$0\"
	
#else
#	#if [ "\$Architecture" != "" ]; then	
	
#endif

# ACTIVATE_SECTION_B create link to your makefile into extensions.active/ to add makefile to your project
createLink \$Dir_Extensions/makefile.$Name \$Dir_ExtensionsActive/makefile.$Name '' QUIET

# ACTIVATE_SECTION_C activate initialization source-code for this extension 
createLink \$Dir_Extensions/$ExtensionSourceFile \$Dir_ExtensionsActive/ '' QUIET

# ACTIVATE_SECTION_D call other activate-scripts
# activate.500_ttc_memory.sh QUIET "\$0"


END_OF_ACTIVATE
  createActivateScriptTail $Name ../extensions/
  #}
  
  if [ "1" == "0" ]; then #{ create symbolic link from extension folder into every PROJECT_FOLDER/additionals/ to provide extra source code and headers
    # Activate line below and change SUBFOLDER to your needs
    addLine ../scripts/createLinks.sh "rm 2>/dev/null $INSTALLPATH; ln -sv \$Source/TheToolChain/InstallData/${INSTALLPATH}/SUBFOLDER $INSTALLPATH"
  fi #} 
  if [ "1" == "0" ]; then #{ create regression test for your extension
  
    Name="650_${EXTENSION_NAME}_regression"  
    createExtensionSourcefileHead ${Name}    #{ create initializer code for your extension
  
    # Below you may write C-code that will automatically being placed inside extensions.active/ttc_extensions_active.c during _/compile.sh
    # Every #include directive will automatically being added to extensions.active/ttc_extensions_active.h
    #
    cat <<END_OF_SOURCEFILE >>$ExtensionSourceFile

#include "${Name}.h"
${Name}_start();

END_OF_SOURCEFILE
    createExtensionSourcefileTail ${Name} #}    
    
    createExtensionMakefileHead ${Name}      #{ create makefile
    cat <<END_OF_MAKEFILE >>$ExtensionMakeFile # variable set by createExtensionMakefileHead() 

# Every regression test should set this to enable extra safety checks
COMPILE_OPTS += -DTTC_REGRESSION

# additional constant defines
#COMPILE_OPTS += -D

# additional directories to search for header files
#INCLUDE_DIRS += -I additionals/$Name/
#INCLUDE_DIRS += -I

# additional directories to search for C-Sources
#vpath %.c 

# additional object files to be compiled
MAIN_OBJS += regression_${EXTENSION_NAME}.o

END_OF_MAKEFILE
    createExtensionMakefileTail ${Name} #}
    createActivateScriptHead $Name ../extensions/ "$0 2" "PLACE YOUR INFO HERE FOR $0" #{ create activate script
    cat <<END_OF_ACTIVATE >>$ActivateScriptFile
# available variables (-> scripts/installFuncs.sh:createActivateScriptHead())
#
# Paths to certain directories in current project folder
#   \$Dir_Extensions        -> extensions/
#   \$Dir_ExtensionsLocal   -> extensions.local/
#   \$Dir_ExtensionsActive  -> extensions.active/
#   \$Dir_Additionals       -> additionals/

# ACTIVATE_SECTION_A remove activated variants of same type
# rm 2>/dev/null \$Dir_ExtensionsActive/*${INSTALLPATH}_*

# ACTIVATE_SECTION_B create link to your makefile into extensions.active/ to add makefile to your project
createLink \$Dir_Extensions/makefile.$Name \$Dir_ExtensionsActive/makefile.$Name '' QUIET

# ACTIVATE_SECTION_C activate initialization source-code for this extension 
createLink \$Dir_Extensions/$ExtensionSourceFile \$Dir_ExtensionsActive/ '' QUIET

# ACTIVATE_SECTION_D call other activate-scripts
activate.${INSTALLPATH}.sh QUIET "\$0"


END_OF_ACTIVATE
    createActivateScriptTail $Name ../extensions/
    #}

  fi #}
  if [ "1" == "1" ]; then #{ create usage example for your extension
  
    Name="600_example_${EXTENSION_NAME}"  
    createExtensionSourcefileHead ${Name}    #{ create initializer code for your extension
  
    # Below you may write C-code that will automatically being placed inside extensions.active/ttc_extensions_active.c during _/compile.sh
    # Every #include directive will automatically being added to extensions.active/ttc_extensions_active.h
    #
    cat <<END_OF_SOURCEFILE >>$ExtensionSourceFile

#include "../examples/example_${EXTENSION_NAME}.h"
example_${EXTENSION_NAME}_start();

END_OF_SOURCEFILE
    createExtensionSourcefileTail ${Name} #}    
    
    createExtensionMakefileHead ${Name}      #{ create makefile
    cat <<END_OF_MAKEFILE >>$ExtensionMakeFile # variable set by createExtensionMakefileHead() 

# additional constant defines
#COMPILE_OPTS += -D

# additional directories to search for header files
#INCLUDE_DIRS += -I additionals/$Name/

# additional directories to search for C-Sources
#vpath %.c 

# additional object files to be compiled
MAIN_OBJS += example_${EXTENSION_NAME}.o

END_OF_MAKEFILE
    createExtensionMakefileTail ${Name} #}
    createActivateScriptHead $Name ../extensions/ "$0 2" "Usage example for extension ${EXTENSION_NAME}" #{ create activate script
    cat <<END_OF_ACTIVATE >>$ActivateScriptFile
# available variables (-> scripts/installFuncs.sh:createActivateScriptHead())
#
# Paths to certain directories in current project folder
#   \$Dir_Extensions        -> extensions/
#   \$Dir_ExtensionsLocal   -> extensions.local/
#   \$Dir_ExtensionsActive  -> extensions.active/
#   \$Dir_Additionals       -> additionals/

# ACTIVATE_SECTION_A remove activated variants of same type
# rm 2>/dev/null \$Dir_ExtensionsActive/*${INSTALLPATH}_*

# ACTIVATE_SECTION_B create link to your makefile into extensions.active/ to add makefile to your project
createLink \$Dir_Extensions/makefile.$Name \$Dir_ExtensionsActive/makefile.$Name '' QUIET

# ACTIVATE_SECTION_C activate initialization source-code for this extension 
createLink \$Dir_Extensions/$ExtensionSourceFile \$Dir_ExtensionsActive/ '' QUIET

# ACTIVATE_SECTION_D call other activate-scripts
activate.${INSTALLPATH}.sh                 QUIET "\$0"
activate.450_ttc_network_driver_6lowpan.sh QUIET "\$0"
activate.500_ttc_network.sh                QUIET "\$0"
activate.500_ttc_timer.sh                  QUIET "\$0"
activate.500_ttc_usart.sh                  QUIET "\$0"
activate.500_ttc_gpio.sh                   QUIET "\$0"
activate.500_ttc_random.sh                 QUIET "\$0"

END_OF_ACTIVATE
    createActivateScriptTail $Name ../extensions/
    #}

  fi #}
    
  cd "$OldPWD"
  echo "Installed successfully: $INSTALLPATH"
#}
else                            #{ Install failed
  echo "failed to install $INSTALLPATH"
  exit 10
fi #}

cd ..
#} IMPLEMENT YOUR INSTALL SCRIPT ABOVE -----------------------------------------------

cd "$StartPath"
applyTargetUserAndGroup "$INSTALLPATH"

exit 0
