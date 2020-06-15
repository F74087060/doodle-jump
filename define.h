#ifndef DEFINE_H
#define DEFINE_H

#define VIEW_WIDTH 600
#define VIEW_HEIGHT 800
#define BUTTON_WIDTH 175
#define PLAYER_WIDTH 120
#define GHOST_WIDTH 100
#define GHOST_RARITY 3
#define FALLING_PLATFORM_RARITY 15
#define MULTIPLIER_RARITY 20
#define SPRING_BOOTS_WIDTH 30
#define SPRING_BOOTS_RARITY 50
#define MOVE_RANGE 200
#define PLATFORM_WIDTH 120
#define PLATFORM_ONSCREEN 6
#define OFFSET 20

#define BACKGROUND_PATH ":/resource/background.png"
#define PLATFORM_PATH ":/resource/platform.png"
#define STOP_PLATFORM_PATH ":/resource/stopplatform.png"
#define BOOST_PLATFORM_PATH ":/resource/boostplatform.png"
#define PLAYER_LEFT_PATH ":/resource/player_left.png"
#define PLAYER_RIGHT_PATH ":/resource/player_right.png"
#define PLAYER_SHOOT_PATH ":/resource/player_shoot.png"
#define PROJECTILE_PATH ":/resource/projectile.png"
#define GHOST_PATH ":/resource/ghost.png"
#define FALLING_PLATFORM_PATH ":/resource/fallingplatform.png"
#define MULTIPLIER_PATH_1 ":/resource/multiplier1x.png"
#define MULTIPLIER_PATH_3 ":/resource/multiplier2x.png"
#define MULTIPLIER_PATH_5 ":/resource/multiplier5x.png"
#define MULTIPLIER_PATH_10 ":/resource/multiplier10x.png"
#define MULTIPLIER_PATH_200 ":/resource/multiplier.png"
#define SPRING_BOOTS_PATH ":/resource/spring_boots.png"
#define PAUSE_MENU_PATH ":/resource/pause.png"
#define MAIN_MENU_PATH ":/resource/mainmenu.png"
#define PLAY_PATH ":/resource/play.png"
#define PLAY_HOVER_PATH ":/resource/playhover.png"
#define MENU_PATH ":/resource/menu.png"
#define MENU_HOVER_PATH ":/resource/menuhover.png"

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
    HAZARD_TYPE,
    PROJECTILE_TYPE,
    GAMEPROPS_TYPE,
    NUMBER_OF_DATA
};

enum objectType{
    PLATFORM,
    HAZARD,
    PROJECTILE,
    GAMEPROPS,
    NUMBER_OF_OBJECT
};

enum platformType{
    NORMAL,
    BOOST,
    DROP,
    NUMBER_OF_PLATFORM
};

enum hazardType{
    GHOST,
    FALLING_PLATFORM,
    NUMBER_OF_HAZARD
};

enum gamePropsType{
    MULTIPLIER,
    SPRING_BOOTS,
    NUMBER_OF_GAMEPROPS
};

#endif // DEFINE_H
