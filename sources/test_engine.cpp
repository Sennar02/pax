#include "demo/Main_State.hpp"
#include <unistd.h>

struct Maze_Room
{
public:
    static const u64 FACE_EAST;
    static const u64 FACE_SOUTH;
    static const u64 FACE_WEST;
    static const u64 FACE_NORTH;

    static const u64 FLAG_VISITED;

    static const u64 FACES = 4u;

    static const Store<v2s64, FACES> STEP_VECTOR;
    static const Store<u64, FACES>   MASK_FORW;
    static const Store<u64, FACES>   MASK_BACK;

public:
    u64 dist;
    u64 face;
    u64 flag;

public:
    bool
    is_closed() const;

    bool
    is_corner() const;

    bool
    is_visited() const;
};

const u64 Maze_Room::FACE_EAST  = 1u;
const u64 Maze_Room::FACE_SOUTH = 2u;
const u64 Maze_Room::FACE_WEST  = 4u;
const u64 Maze_Room::FACE_NORTH = 8u;

const u64 Maze_Room::FLAG_VISITED = 1u;

const Store<v2s64, Maze_Room::FACES> Maze_Room::STEP_VECTOR = {
    v2s64 {+1,  0}, // EAST
    v2s64 { 0, +1}, // SOUTH,
    v2s64 {-1,  0}, // WEST,
    v2s64 { 0, -1}, // NORTH
};

const Store<u64, Maze_Room::FACES> Maze_Room::MASK_FORW = {
    Maze_Room::FACE_EAST,
    Maze_Room::FACE_SOUTH,
    Maze_Room::FACE_WEST,
    Maze_Room::FACE_NORTH,
};

const Store<u64, Maze_Room::FACES> Maze_Room::MASK_BACK = {
    Maze_Room::FACE_WEST,
    Maze_Room::FACE_NORTH,
    Maze_Room::FACE_EAST,
    Maze_Room::FACE_SOUTH,
};

bool
Maze_Room::is_closed() const
{
    switch ( face ) {
        pax_case_fall(FACE_EAST)
        pax_case_fall(FACE_SOUTH)
        pax_case_fall(FACE_WEST)
        pax_case_fall(FACE_NORTH)
            return true;
    }

    return false;
}

bool
Maze_Room::is_corner() const
{
    switch ( face ) {
        pax_case_fall(FACE_EAST | FACE_SOUTH)
        pax_case_fall(FACE_EAST | FACE_NORTH)
        pax_case_fall(FACE_WEST | FACE_SOUTH)
        pax_case_fall(FACE_WEST | FACE_NORTH)
            return true;
    }

    return false;
}

bool
Maze_Room::is_visited() const
{
    return bits_test(flag, FLAG_VISITED);
}

struct Maze
{
public:
    Array2d<Maze_Room> array;
    List<v2u64>   stack;

    v2u64 origin;
    u64 count;

public:
    bool
    acquire(v2u64 size);

    bool
    contains(v2u64 index) const;

    bool
    build(u64 limit, v2u64 origin);

    virtual bool
    build_link(v2u64 room) const;

    void
    build_room();

    u64
    distance(v2u64 origin);

    v2u64
    farthest(v2u64 origin);

    void
    write(u64 wait);
};

bool
Maze::acquire(v2u64 size)
{
    if ( array.acquire(size) == false )
        return false;

    return stack.acquire(array.area);
}

bool
Maze::contains(v2u64 index) const
{
    return index(0) < array.size(0) &&
           index(1) < array.size(1);
}

bool
Maze::build(u64 limit, v2u64 origin)
{
    if ( contains(origin) == false )
        return false;

    for ( u64 i = 0; i < array.area; i += 1u )
        array(i) = {};

    stack.clear().insert(origin, 0);

    this->origin = origin;
    this->count  = 0;

    for ( count = 0; count < limit; count += 1u ) {
        if ( stack.count != 0 )
            build_room();
        else break;
    }

    stack.clear();

    return true;
}

bool
Maze::build_link(v2u64 room) const
{
    bool value = false;

    if ( count <= array.area / 8u )
        value |= array(room).face == 0;

    if ( rand() % 2 == 0 )
        value |= array(room).is_closed();

    return value;
}

void
Maze::build_room()
{
    static Store<u64, 4u> indeces = {0, 1, 2, 3};

    v2u64 room = stack.remove(stack.count - 1u).item;
    v2u64 next = {};
    u64   face = 0;

    if ( rand() % 5 == 0 ) list_shuffle(stack);

    store_shuffle(indeces);

    for ( u64 i = 0; i < Maze_Room::FACES; i += 1u ) {
        face = indeces(i);
        next = room + Maze_Room::STEP_VECTOR(face);

        if ( contains(next) && build_link(next) ) {
            if ( array(next).face == 0 )
                stack.insert(next, stack.count);

            array(room).face |= Maze_Room::MASK_FORW(face);
            array(next).face |= Maze_Room::MASK_BACK(face);
        }
    }
}

u64
Maze::distance(v2u64)
{
    return 0;
}

v2u64
Maze::farthest(v2u64 origin)
{
    return origin;
}

void
Maze::write(u64 wait)
{
    static const u64 limit = 16u;
    static const u64 size  = 3u;

    static const Store<const char*, limit * size> lines = {
        "     ",
        "     ",
        "     ",

        "     ",
        "  @ #",
        "     ",

        "     ",
        "  @  ",
        "  #  ",

        "     ",
        "  @ #",
        "  #  ",

        "     ",
        "# @  ",
        "     ",

        "     ",
        "# @ #",
        "     ",

        "     ",
        "# @  ",
        "  #  ",

        "     ",
        "# @ #",
        "  #  ",

        "  #  ",
        "  @  ",
        "     ",

        "  #  ",
        "  @ #",
        "     ",

        "  #  ",
        "  @  ",
        "  #  ",

        "  #  ",
        "  @ #",
        "  #  ",

        "  #  ",
        "# @  ",
        "     ",

        "  #  ",
        "# @ #",
        "     ",

        "  #  ",
        "# @  ",
        "  #  ",

        "  #  ",
        "# @ #",
        "  #  ",
    };

    system("clear");

    for ( u64 i = 0; i < array.size(1); i += 1u ) {
        for ( u64 k = 0; k < size; k += 1u ) {

            for ( u64 j = 0; j < array.size(0); j += 1u )
                printf("%s%s%s ", "\x1b[94m", lines(array(j, i).face * size + k), "\x1b[0m");

            printf("\n");
        }
    }

    for ( u64 i = 0; i < array.size(1); i += 1u ) {
        for ( u64 j = 0; j < array.size(0); j += 1u )
            printf("%3lu ", array(j, i).dist);

        printf("\n");
    }

    usleep(wait);
}

void
test_engine()
{
    Maze maze;

    srand(time(0));

    maze.acquire({29u, 9u});
    maze.build(maze.array.area / 4u, {
        maze.array.size(0) / 2u,
        maze.array.size(1) / 2u,
    });

    maze.write(0);
}

// bool
// maze_build_room(Maze& maze, v2u64 room, v2u64 next, u64 face)
// {
//     u64  kind = maze.rooms(next).kind;
//     bool cond = (kind == 0);

//     if ( maze.perc >= maze.rooms.area / 8u )
//         cond = false;

//     if ( cond || (is_room_dead_end(maze, next) && rand() % 2 == 0) ) {
//         maze.rooms(room).kind |= ROOM_MASKS_POS(face);
//         maze.rooms(next).kind |= ROOM_MASKS_NEG(face);

//         if ( kind == 0 )
//             return true;
//     }

//     return false;
// }

// bool
// maze_build(Maze& maze, v2u64 origin, u64 rooms)
// {
//     v2u64 room = {};
//     v2u64 next = {};
//     u64   face = 0;

//     if ( maze_contains(maze, origin) == false )
//         return false;

//     maze.track.count = 0;
//     maze.perc = 0;

//     for ( u64 i = 0; i < maze.rooms.area; i += 1u )
//         maze.rooms(i).kind = 0;

//     maze.track.insert(origin, 0);
//     maze.origin = origin;

//     for ( ; maze.perc < rooms; maze.perc += 1u) {
//         if ( maze.track.is_empty() )
//             return true;


//         if ( rand() % (u64) ((f64) maze.rooms.area / (f64) maze.perc + 1) == 0 )
//             maze.track.perm();

//         room = maze.track
//             .remove(maze.track.count - 1u).item;

//         ROOM_FACES_TABLE.perm();

//         for ( u64 j = 0; j < ROOM_FACES; j += 1u ) {
//             face = ROOM_FACES_TABLE(j);
//             next = room + ROOM_VECTS(face);

//             if ( maze_contains(maze, next) == false ) continue;

//             if ( maze_build_room(maze, room, next, face) )
//                 maze.track.insert(next, maze.track.count);

//             system("clear");

//             for ( u64 i = 0; i < maze.rooms.size(1); i += 1u ) {
//                 for ( u64 k = 0; k < ROOM_SIZE; k += 1u ) {
//                     for ( u64 j = 0; j < maze.rooms.size(0); j += 1u ) {
//                         Room room = maze.rooms(j, i);

//                         printf("%s%s%s ",
//                             ROOM_STYLES(room.kind != 0),
//                             ROOM_STRINGS(room.kind * ROOM_SIZE + k),
//                             ROOM_STYLES(0));
//                     }

//                     printf("\n");
//                 }
//             }

//             usleep(5000);
//         }
//     }

//     maze.track.count = 0;

//     return true;
// }

// bool
// maze_distance(Maze& maze, v2u64 origin)
// {
//     v2u64 room  = {};
//     v2u64 next  = {};
//     u64   dist  = 0;
//     u64   index = 0;

//     if ( maze_contains(maze, origin) == false )
//         return false;

//     maze.track.count = 0;

//     for ( u64 r = 0; r < maze.rooms.size(1); r += 1u ) {
//         for ( u64 c = 0; c < maze.rooms.size(0); c += 1u ) {
//             room = {c, r};

//             if ( maze.rooms(room).kind != 0 )
//                 maze.track.insert(room, maze.track.count);

//             maze.rooms(room).dist = maze.rooms.area;
//         }
//     }

//     maze.rooms(origin).dist = 0;

//     while ( maze.track.is_empty() == false ) {
//         index = 0;

//         for ( u64 i = 0; i < maze.track.count; i += 1u ) {
//             v2u64 value = maze.track(index);
//             v2u64 other = maze.track(i);

//             if ( maze.rooms(value).dist > maze.rooms(other).dist )
//                 index = i;
//         }

//         room = maze.track.remove(index).item;

//         for ( u64 i = 0; i < ROOM_FACES; i += 1u ) {
//             next = room + ROOM_VECTS(i);

//             if ( bits_test(maze.rooms(room).kind, ROOM_MASKS_POS(i)) ) {
//                 if ( maze_contains(maze, next) ) {
//                     dist = maze.rooms(room).dist + 1u;

//                     if ( dist < maze.rooms(next).dist )
//                         maze.rooms(next).dist = dist;
//                 }
//             }
//         }
//     }

//     maze.track.count = 0;

//     return true;
// }

// v2u64
// maze_farthest(Maze& maze, v2u64 origin)
// {
//     v2u64 room = origin;
//     v2u64 next = {};
//     v2u64 temp = {};

//     maze.track.count = 0;
//     maze.track.insert(room, maze.track.count);

//     while ( maze.track.is_empty() == false ) {
//         temp = maze.track.remove(0).item;

//         maze.rooms(temp).flags = bits_write(
//             maze.rooms(temp).flags, Room::FLAG_VISITED
//         );

//         if ( maze.rooms(temp).dist < maze.rooms(room).dist )
//             room = temp;

//         system("clear");
//         printf("stack count = %lu\n", maze.track.count);
//         usleep(1000);

//         for ( u64 j = 0; j < ROOM_FACES; j += 1u ) {
//             next = room + ROOM_VECTS(j);

//             if ( bits_test(maze.rooms(temp).kind, ROOM_MASKS_POS(j)) ) {
//                 if ( bits_test(maze.rooms(next).flags, Room::FLAG_VISITED) == false )
//                     maze.track.insert(next, maze.track.count);
//             }
//         }
//     }

//     return room;
// }
