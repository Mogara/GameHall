# GameHall

[![Build Status](https://travis-ci.org/Mogara/GameHall.svg?branch=dev)](https://travis-ci.org/Mogara/GameHall)

Game Hall of Cardirector. This is the Entrance of Cardirector Store.

## Develop mode
+ ### features:
  + Refresh your apps automactically when there are changes on QML file. No need to rebuild the whole project in develop mode.
  + *qml.qrc* will not be used when the project is built.
+ ### Usage:
  + By default, the develop mode is off.
  + You can trigger **DEVELOP_MODE** by using
    ```bash
    cmake -D DEVELOP_MODE=ON $(project_path)
    ```