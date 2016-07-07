#!/bin/bash
#
#
#  Install script for generic network support 
#
#  Initial Script written by Gregor Rebel 2010-2012.
# 
#  Published under GNU Lesser General Public License
#  Check LEGAL.txt for details.
#
# Tested successfully on:
# XUbuntu 11.10 x64

source scripts/installFuncs.sh
checkUserRoot "$1" "$2"

StartPath="`pwd`"
INSTALLPATH="500_ttc_network"
dir "$INSTALLPATH"
cd "$INSTALLPATH"

#{ IMPLEMENT YOUR INSTALL SCRIPT BELOW -----------------------------------------------

  Name="$INSTALLPATH"
  createExtensionSourcefileHead ${Name}    #{ (create initializer code)
  
  # Below you may write C-code that will automatically being placed inside extensions.active/ttc_extensions_active.c during _/compile.sh
  # Every #include directive will automatically be added to extensions.active/ttc_extensions_active.h
  #
  cat <<END_OF_SOURCEFILE >>$ExtensionSourceFile

    #include "network/ttc_network.h"
    ttc_network_prepare();

END_OF_SOURCEFILE
  createExtensionSourcefileTail ${Name} #}    
  createExtensionMakefileHead ${Name}      #{ create makefile
  cat <<END_OF_MAKEFILE >>$ExtensionMakeFile # variable set by createExtensionMakefileHead() 

MAIN_OBJS += ttc_network.o

END_OF_MAKEFILE
  createExtensionMakefileTail ${Name} #}
  createActivateScriptHead $Name ../extensions/ "$0" "Architecture independent support for Universal Synchronous Asynchronous Serial Receiver Transmitter (RADIO)" #{
  cat <<END_OF_ACTIVATE >>$ActivateScriptFile
# available variables (-> scripts/installFuncs.sh:createActivateScriptHead())
#
# Paths to certain directories in current project folder
#   \$Dir_Extensions        -> extensions/
#   \$Dir_ExtensionsLocal   -> extensions.local/
#   \$Dir_ExtensionsActive  -> extensions.active/
#   \$Dir_Additionals       -> additionals/

# remove activated variants of same type
# rm 2>/dev/null \$Dir_Additionals/${Name}_*

Architecture=\`ls -f extensions.active/*network*\`

if [ "\$Architecture" != "" ]; then

  # create links into extensions.active/
  createLink "\$Dir_Extensions/makefile.$Name" "\$Dir_ExtensionsActive/makefile.$Name" '' QUIET
else
  echo "$0 - ERROR: no supported architecture found!"
fi

END_OF_ACTIVATE
  createActivateScriptTail $Name ../extensions/
  #}
  echo "Installed successfully: $Name"
  
cd ..
#} IMPLEMENT YOUR INSTALL SCRIPT ABOVE -----------------------------------------------

cd "$StartPath"
applyTargetUserAndGroup "$INSTALLPATH"

exit 0
