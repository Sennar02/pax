#ifndef DEMO_MAZE_HPP
#define DEMO_MAZE_HPP

#include "define.hpp"

struct Room_Face
{
    static const u64 NORTH = 1u;
    static const u64 EAST  = 2u;
    static const u64 SOUTH = 4u;
    static const u64 WEST  = 8u;
};

struct Room
{
    u64 kind;
    u64 dist;
};

static const u64 ROOM_FACES = 4u;

static const Store<u64, ROOM_FACES> ROOM_MASKS_POS = {
    Room_Face::NORTH,
    Room_Face::EAST,
    Room_Face::SOUTH,
    Room_Face::WEST,
};

static const Store<u64, ROOM_FACES> ROOM_MASKS_NEG = {
    Room_Face::SOUTH,
    Room_Face::WEST,
    Room_Face::NORTH,
    Room_Face::EAST,
};

static const Store<v2s64, ROOM_FACES> ROOM_VECTS = {
    v2s64 { 0, -1},
    v2s64 { 1,  0},
    v2s64 { 0,  1},
    v2s64 {-1,  0},
};

static const u64 ROOM_KINDS = 16u;

bool
is_room_dead_end(Room room)
{
    switch ( room.kind ) {
        pax_case_fall(Room_Face::NORTH)
        pax_case_fall(Room_Face::EAST)
        pax_case_fall(Room_Face::SOUTH)
        pax_case_fall(Room_Face::WEST)
            return true;
    }

    return false;
}

struct Maze
{
public:
    Array2d<Room> rooms;

    List<v2u64> stack;

    u64 steps;

    v2u64 origin;
    v2u64 finish;

    bool
    acquire(v2u64 size);

    bool
    generate(v2u64 origin);
};

bool
Maze::acquire(v2u64 size)
{
    if ( rooms.acquire(size) == false )
        return false;

    return stack.acquire(size(0) * size(1));
}

bool
Maze::generate(v2u64 origin)
{
    u64 index = 0;
    u64 dist = 0;
    v2u64 room = {};

    Array<u64> table = array_create<u64>(4u);

    for ( u64 i = 0 ; i < table.size; i += 1u )
        table(i) = i;

    if ( origin(0) < rooms.size(0) &&
         origin(1) < rooms.size(1)
    ) {
        this->origin = origin;
        this->finish = origin;

        for ( u64 i = 0; i < rooms.area; i += 1u )
            rooms(i).kind = 0, rooms(i).dist = 1;

        stack.insert(origin, stack.count);

        for ( u64 i = 0; i < steps + 1u; i += 1u ) {
            // If there are no more rooms to visit, it ends the loop.
            if ( stack.is_empty() ) break;

            // Extracts the index of the next room to visit.
            index = rand() % stack.count / 2u;
            // Also reads the state of the room.
            room = stack(index);

            for ( u64 j = 0; j < table.size; j += 1u )
                table.swap(rand() % table.size, rand() % table.size);

            for ( u64 j = 0; j < ROOM_FACES; j += 1u ) {
                v2u64 next = vector_create<u64>(ROOM_VECTS(table(j)) + room);

                if ( next(0) < rooms.size(0) && next(1) < rooms.size(1) ) {
                    if ( rooms(next).kind == 0 ) {
                        rooms(room).kind |= ROOM_MASKS_POS(table(j));
                        rooms(next).kind |= ROOM_MASKS_NEG(table(j));

                        dist             = rooms(room).dist + 1u;
                        rooms(next).dist = dist;

                        stack.insert(next, stack.count);
                        index = MAX_U64;
                        break;
                    }

                    if ( rand() % 2 == 0 ) {
                        rooms(room).kind |= ROOM_MASKS_POS(table(j));
                        rooms(next).kind |= ROOM_MASKS_NEG(table(j));
                    }

                    if ( is_room_dead_end(rooms(next)) ) {
                        if ( dist > rooms(origin).dist )
                            origin = next;
                    }
                }
            }

            if ( index != MAX_U64 )
                stack.remove(index);
        }

        // for ( u64 i = 0; i < chain.count; i += 1u ) {
        //     invoker = invoker_create<bool, Maze>(chain(i));

        //     if ( invoker.invoke(pax_self) == false )
        //         return false;
        // }

        return true;
    }

    return false;
}

bool
maze_place_room(Maze& maze, v2u64 room, v2u64 next, u64 face)
{
    u64 dist = 0;

    if ( maze.rooms(next).kind == 0 ) {
        if ( maze.stack.insert(next, maze.stack.count).full == false )
            return false;

        maze.rooms(room).kind |= ROOM_MASKS_POS(face);
        maze.rooms(next).kind |= ROOM_MASKS_NEG(face);

        dist = maze.rooms(room).dist + 1u;

        maze.rooms(next).dist = dist;
    }

    return true;
}

void
maze_join_rooms(Maze& maze, v2u64 room, v2u64 next, u64 face)
{
    u64 space = 2;

    if ( is_room_dead_end(maze.rooms(next)) ) {
        if ( rand() % space != 0 ) {
            maze.rooms(room).kind |= ROOM_MASKS_POS(face);
            maze.rooms(next).kind |= ROOM_MASKS_NEG(face);
        }
    }
}

void
maze_place_finish()
{}

bool
maze_generate(Maze& maze)
{
    u64   index = 0;
    v2u64 room  = {};
    v2u64 next  = {};

    for ( u64 i = 0; i < maze.steps; i += 1u ) {
        if ( maze.stack.is_empty() ) return true;

        index = rand() % maze.stack.count;
        room  = maze.stack(index);

        for ( u64 j = 0; j < ROOM_FACES; j += 1u ) {
            next = vec2d_create<u64>(ROOM_VECTS(j) + room);

            if ( next(0) < maze.rooms.size(0) &&
                 next(1) < maze.rooms.size(1)
            ) {
                if ( maze_place_room(maze, room, next, j) == false )
                    return false;

                maze_join_rooms(maze, room, next, j);
                maze_place_finish();

                if ( maze.stack.remove(index).full == false )
                    return false;

                break;
            }
        }
    }

    return true;
}

#endif // DEMO_MAZE_HPP
