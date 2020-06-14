#ifndef DEFINE_H
#define DEFINE_H

#define VIEW_WIDTH 600
#define VIEW_HEIGHT 800
#define PLAYER_WIDTH 120
#define PLATFORM_WIDTH 120
#define OFFSET 20

#define BACKGROUND_PATH ":/resource/background.png"
#define PLATFORM_PATH ":/resource/platform.png"
#define BOOST_PLATFORM_PATH ":/resource/boostplatform.png"
#define PLAYER_LEFT_PATH ":/resource/player_left.png"
#define PLAYER_RIGHT_PATH ":/resource/player_right.png"

enum verticalDirection{
    UP,
    DOWN
};

enum horizontalDirection{
    LEFT,
    RIGHT,
    STOP
};

enum Data{
    TYPE,
    PLATFORM_TYPE,
    NUMBER_OF_DATA
};

enum objectType{
    PLATFORM,
    NUMBER_OF_OBJECT
};

enum platformType{
    NORMAL,
    BOOST,
    NUMBER_OF_PLATFORM
};

#endif // DEFINE_H
