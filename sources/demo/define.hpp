#ifndef DEMO_DEFINE_HPP
#define DEMO_DEFINE_HPP

#include <pax/Engine/import.hpp>

using namespace pax;

#define DEMO_SHOW_TEXT_GRID false

/**
 * Title of the display.
 */
static const String PAX_TITLE = string_create("Pax Tibi", {0, 9u});

/**
 * Size of a single tile in pixels.
 */
static const v2f64 PAX_TILE_SIZE = {48.0, 48.0};

/**
 * Half of a single tile in pixels.
 */
static const v2f64 PAX_TILE_HALF = PAX_TILE_SIZE / 2.0;

/**
 * Size of the view in tiles.
 */
static const v2f64 PAX_VIEW_SIZE = {21.0, 9.0};

/**
 * Half of the view in tiles.
 */
static const v2f64 PAX_VIEW_HALF = PAX_VIEW_SIZE / 2.0;

/**
 * Size of each grid in tiles.
 */
static const v2u64 PAX_GRID_SIZE = {500u, 200u};

/**
 * Total amount of actors in the game.
 */
static const u64 PAX_MAX_ACTORS = 20000u;

#endif // DEMO_DEFINE_HPP