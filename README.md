# GameHall

[![Build Status](https://travis-ci.org/Mogara/GameHall.svg?branch=dev)](https://travis-ci.org/Mogara/GameHall)

Game Hall of Cardirector. This is the Entrance of Cardirector Store.

## Develop mode
+ ### features:
  + Refresh your apps automactically when there are changes on QML file. No need to rebuild the whole project in develop mode.
  + *qml.qrc* will not be used when the project is built.
  + Add log output console support
+ ### Usage:
  + You can trigger DEVELOP_MODE by adding ***additional arguments*** in Project aspect of QtCreator with "CONFIG+=develop_mode" or `qmake CONFIG+=develop_mode \<path to pro>` if you prefer cli.
  
  + Because we only check whether the variable exists in .pro file,  actually any value is ok. 
  
  + You can trigger log output console by `F12`, clear log by 'Ctrl + L'.
