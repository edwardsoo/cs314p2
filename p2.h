// Geometry values
#define SPHERE_SLICES 8
#define SPHERE_STACKS 8
#define DISK_SLICES 256
#define DISK_LOOPS 256
#define CONE_SLICES 4
#define CONE_STACKS 256
#define FULL_ROTATION 360.0f
#define MATRIX_SIZE 16

// 3f RGB INDICE
#define RED 0
#define GREEN RED+1
#define BLUE GREEN+1
#define COLOR_BASES BLUE+1

// Ship variables
typedef struct ship {
	GLfloat x,y,z,lookat_x,lookat_y,lookat_z,up_x,up_y,up_z;
	GLfloat current_m[16];
	GLfloat yaw,roll,pitch,forward;
	unsigned int mode,current_planet;
	GLfloat geo_dist,move_speed;
} ship;

// Ships properties
#define DEFAULT_SPEED 10.0f
#define SPEED_UNIT 10.0f
#define SPEED_LIMIT DEFAULT_SPEED*10
#define LOOKAT_MOVE_UNIT 5.0f
#define UP_MOVE_UNIT 0.1f
#define ROTATE_UNIT 10.0f
#define DEFAULT_GEO_DIST 5.0f
#define MAX_GEO_DIST 5000.0f

#define SCOUT_INIT_X 0
#define SCOUT_INIT_Y 100
#define SCOUT_INIT_Z 500

#define MOTHER_INIT_X 0
#define MOTHER_INIT_Y 100
#define MOTHER_INIT_Z 510

#define SCOUT_BODY_SIZE 1.0
#define SCOUT_WING_LENGTH 1.0
#define SCOUT_WING_WIDTH 0.5
#define SCOUT_PANEL_WIDTH 0.1
#define SCOUT_PANEL_LENDTH 2.0
#define SCOUT_PANEL_HEIGHT 1.0
#define SCOUT_PANEL_ANGLE 45

#define MOTHER_BODY_LENGTH 9.0
#define MOTHER_BODY_WIDTH 3.0
#define MOTHER_BODY_HEIGHT 1.0
#define MOTHER_PLATFORM_LENGTH 1.5
#define MOTHER_PLATFORM_WIDTH 0.5
#define MOTHER_PLATFORM_HEIGHT 1.0
#define MOTHER_DECK_WIDTH 2.5
#define MOTHER_DECK_LENDTH 2.0
#define MOTHER_DECK_HEIGHT 0.3

// Sun and planet properties
#define ORBIT_WEIGHT 0.2

#define ORBIT_ALPHA 0.3f
#define WHITE 1.0,1.0,1.0
#define GREY 0.5,0.5,0.5
#define BROWN 0.8,0.7,0.6
#define SUN_COLOR {1.0,0.5,0.1}
#define MERCURY_COLOR {0.5,0.5,0.7}
#define VENUS_COLOR {1,0.8,0}
#define EARTH_COLOR {0,0.6,0.9}
#define MOON_COLOR {0.7,0.7,0.7}
#define MARS_COLOR {1.0,0,0}
#define JUPITER_COLOR {0.75,0.67,0.63}
#define SATURN_COLOR {0.93,0.78,0.53}
#define URANUS_COLOR {0.53,0.67,0.8}
#define NEPTUNE_COLOR {0.36,0.43,0.60}
#define PLUTO_COLOR {0.5,0.5,0.5}

#define SUN_RADIUS EARTH_RADIUS*5.0
#define MERCURY_RADIUS EARTH_RADIUS/2.0
#define VENUS_RADIUS EARTH_RADIUS
#define EARTH_RADIUS 5.0
#define MOON_RADIUS EARTH_RADIUS/2.0
#define MARS_RADIUS EARTH_RADIUS/1.5
#define JUPITER_RADIUS EARTH_RADIUS*4.0
#define SATURN_RADIUS EARTH_RADIUS*3.0
#define SATURN_RING_INNER_RAD SATURN_RADIUS+EARTH_RADIUS*1.0
#define SATURN_RING_OUTER_RAD SATURN_RING_INNER_RAD+EARTH_RADIUS*2.0
#define URANUS_RADIUS EARTH_RADIUS*2.0
#define NEPTUNE_RADIUS EARTH_RADIUS*2.0
#define PLUTO_RADIUS EARTH_RADIUS/2.0
#define SATURN_RING_ANGLE 30.0

#define SUN_ORBIT_RADIUS 0.0
#define MERCURY_ORBIT_RADIUS SUN_RADIUS+MERCURY_RADIUS+5.0*EARTH_RADIUS
#define VENUS_ORBIT_RADIUS MERCURY_ORBIT_RADIUS+VENUS_RADIUS+3.0*EARTH_RADIUS
#define EARTH_ORBIT_RADIUS VENUS_ORBIT_RADIUS+EARTH_RADIUS+3.0*EARTH_RADIUS
#define MOON_ORBIT_RADIUS 3.0*MOON_RADIUS+1*EARTH_RADIUS
#define MARS_ORBIT_RADIUS EARTH_ORBIT_RADIUS+MOON_ORBIT_RADIUS+MARS_RADIUS+3.0*EARTH_RADIUS
#define JUPITER_ORBIT_RADIUS MARS_ORBIT_RADIUS+JUPITER_RADIUS+3.0*EARTH_RADIUS
#define SATURN_ORBIT_RADIUS JUPITER_ORBIT_RADIUS+SATURN_RING_OUTER_RAD+5.0*EARTH_RADIUS
#define URANUS_ORBIT_RADIUS SATURN_ORBIT_RADIUS+URANUS_RADIUS+5.0*EARTH_RADIUS
#define NEPTUNE_ORBIT_RADIUS URANUS_ORBIT_RADIUS+NEPTUNE_RADIUS+3.0*EARTH_RADIUS
#define PLUTO_ORBIT_RADIUS NEPTUNE_ORBIT_RADIUS+PLUTO_RADIUS+7.0*EARTH_RADIUS
#define PLUTO_ORBIT_ANGLE -15.0

#define SUN_AXLE_ANGLE 0
#define MERCURY_AXLE_ANGLE 10
#define VENUS_AXLE_ANGLE 30
#define EARTH_AXLE_ANGLE 20
#define MARS_AXLE_ANGLE 45
#define JUPITER_AXLE_ANGLE 10
#define SATURN_AXLE_ANGLE 35
#define URANUS_AXLE_ANGLE 20
#define NEPTUNE_AXLE_ANGLE 20
#define PLUTO_AXLE_ANGLE 30
#define MOON_AXLE_ANGLE 0

// everything is relative to earth's spin
#define EARTH_SPIN_UNIT 10.0f
#define SUN_SPIN_UNIT EARTH_SPIN_UNIT/24.0
#define MERCURY_SPIN_UNIT EARTH_SPIN_UNIT/59.0
#define VENUS_SPIN_UNIT EARTH_SPIN_UNIT/243.0
#define MOON_SPIN_UNIT 0.0
#define MARS_SPIN_UNIT EARTH_SPIN_UNIT
#define JUPITER_SPIN_UNIT EARTH_SPIN_UNIT*24.0/10.0
#define SATURN_SPIN_UNIT JUPITER_SPIN_UNIT
#define URANUS_SPIN_UNIT EARTH_SPIN_UNIT*24.0/17.0
#define NEPTUNE_SPIN_UNIT URANUS_SPIN_UNIT
#define PLUTO_SPIN_UNIT EARTH_SPIN_UNIT/6.0

#define SUN_ORBIT_UNIT 0.0
#define MERCURY_ORBIT_UNIT EARTH_SPIN_UNIT/88.0
#define VENUS_ORBIT_UNIT EARTH_SPIN_UNIT/225.0
#define EARTH_ORBIT_UNIT EARTH_SPIN_UNIT/365.0
#define MOON_ORBIT_UNIT EARTH_SPIN_UNIT/30.0
#define MARS_ORBIT_UNIT EARTH_SPIN_UNIT/687.0
#define JUPITER_ORBIT_UNIT EARTH_SPIN_UNIT/4333.0
#define SATURN_ORBIT_UNIT EARTH_SPIN_UNIT/10759.0
#define URANUS_ORBIT_UNIT EARTH_SPIN_UNIT/30684.0
#define NEPTUNE_ORBIT_UNIT EARTH_SPIN_UNIT/60190.0
#define PLUTO_ORBIT_UNIT EARTH_SPIN_UNIT/90456.0

//  solar system objects indice
#define SUN 0
#define MERCURY SUN+1
#define VENUS MERCURY+1
#define EARTH VENUS+1
#define MARS EARTH+1
#define JUPITER MARS+1
#define SATURN JUPITER+1
#define URANUS SATURN+1
#define NEPTUNE URANUS+1
#define PLUTO NEPTUNE+1
#define MOON PLUTO+1
#define NUM_SPHERE MOON+1
#define SATURN_RING NUM_SPHERE+1
#define NUM_DISKS SATURN_RING+1

const float OBJ_RADIUS[NUM_SPHERE] = {SUN_RADIUS,MERCURY_RADIUS,VENUS_RADIUS,
	EARTH_RADIUS,MARS_RADIUS,JUPITER_RADIUS,SATURN_RADIUS,
	URANUS_RADIUS,NEPTUNE_RADIUS,PLUTO_RADIUS,MOON_RADIUS};

const float OBJ_AXLE_ANGLES[NUM_SPHERE] = {SUN_AXLE_ANGLE,MERCURY_AXLE_ANGLE,VENUS_AXLE_ANGLE,
	EARTH_AXLE_ANGLE,MARS_AXLE_ANGLE,JUPITER_AXLE_ANGLE,SATURN_AXLE_ANGLE,
	URANUS_AXLE_ANGLE,NEPTUNE_AXLE_ANGLE,PLUTO_AXLE_ANGLE,MOON_AXLE_ANGLE};

const float OBJ_ORBIT_RADIUS[NUM_SPHERE] = {SUN_ORBIT_RADIUS,MERCURY_ORBIT_RADIUS,VENUS_ORBIT_RADIUS,
	EARTH_ORBIT_RADIUS,MARS_ORBIT_RADIUS,JUPITER_ORBIT_RADIUS,SATURN_ORBIT_RADIUS,
	URANUS_ORBIT_RADIUS,NEPTUNE_ORBIT_RADIUS,PLUTO_ORBIT_RADIUS,MOON_ORBIT_RADIUS};

const float SPIN_UNITS[NUM_SPHERE] = {SUN_SPIN_UNIT,MERCURY_SPIN_UNIT,VENUS_SPIN_UNIT,
	EARTH_SPIN_UNIT,MARS_SPIN_UNIT,JUPITER_SPIN_UNIT,SATURN_SPIN_UNIT,
	URANUS_SPIN_UNIT,NEPTUNE_SPIN_UNIT,PLUTO_SPIN_UNIT,MOON_SPIN_UNIT};

const float ORBIT_UNITS[NUM_SPHERE] = {SUN_ORBIT_UNIT,MERCURY_ORBIT_UNIT,VENUS_ORBIT_UNIT,
	EARTH_ORBIT_UNIT,MARS_ORBIT_UNIT,JUPITER_ORBIT_UNIT,SATURN_ORBIT_UNIT,
	URANUS_ORBIT_UNIT,NEPTUNE_ORBIT_UNIT,PLUTO_ORBIT_UNIT,MOON_ORBIT_UNIT};

const float OBJ_COLORS[NUM_SPHERE][COLOR_BASES] = {SUN_COLOR,MERCURY_COLOR,VENUS_COLOR,EARTH_COLOR,
	MARS_COLOR,JUPITER_COLOR,SATURN_COLOR,URANUS_COLOR,NEPTUNE_COLOR,PLUTO_COLOR,MOON_COLOR};


// Modes
#define ABS_LOOK_AT 0x1
#define REL_FLYING ABS_LOOK_AT << 1
#define GEO_SYNC REL_FLYING << 1
