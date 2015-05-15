# README #

A patch to the [foamCalc]([http://www.openfoam.org/docs/user/cavity.php#dx5-2400) tool to enable some extra field operations such as min and max.

### Usage ###

The utility works the same way as the standard foamCalc tool, but accepts extra parameters (min, max, volIntegrate, average, grad, scalarMultiply):

    foamCalcEx min <fieldName> [-latestTime] [-time ranges] 
    
    foamCalcEx max <fieldName> [-latestTime] [-time ranges]
    
    foamCalcEx minMax <fieldName> [-latestTime] [-time ranges]
    
    foamCalcEx cellMinMax <fieldName> [-latestTime] [-time ranges]
    
    foamCalcEx volIntegrate <fieldName> [-latestTime] [-time ranges]
    
    foamCalcEx average <fieldName> [-latestTime] [-time ranges]
    
    foamCalcEx grad <fieldName> [-latestTime] [-time ranges]
    
    foamCalcEx laplacian <fieldName> [-latestTime] [-time ranges]
    
    foamCalcEx multiplyDivide <fieldName> multiply/divide -field/value <scalar_value>/<fieldName> [-latestTime] [-time ranges]`

### Build ###
To install, run one of the following group of commands in a terminal window where you have loaded the OpenFOAM environment:

If you have `hg` ([Mercurial](http://en.wikipedia.org/wiki/Mercurial)) installed:

    
    hg clone https://bitbucket.org/akidess/foamcalcex
    cd foamcalcex
    ./Allwmake

If you do not have `hg` ([Mercurial](http://en.wikipedia.org/wiki/Mercurial)) installed or if you're in a country with a more restricted access or unable to use [HTTPS](http://en.wikipedia.org/wiki/HTTP_Secure):
    
    wget http://foamcalcex.googlecode.com/archive/tip.zip -O latest-foamCalcEx.zip
    unzip latest-foamCalcEx.zip
    cd foamcalcex-*
    chmod +x Allwmake postProcessing/Allwmake
    find . -exec touch '{}' \;
    ./Allwmake

### Note ###
Be aware that the [swak4Foam](http://openfoamwiki.net/index.php/Contrib/swak4Foam) utilities [funkySetFields](http://openfoamwiki.net/index.php/Contrib_funkySetFields) and [funkyDoCalc](http://openfoamwiki.net/index.php/Contrib/swak4Foam/README_2.x#.3DfunkyDoCalc.3D) can also be used for post-processing calculations (with longer commandline flags or dictionaries)

Also have a look at the OpenFOAM-Wiki: https://openfoamwiki.net/index.php/Contrib_foamCalcEx