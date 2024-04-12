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
 * Size of a single cell in pixels.
 */
static const v2f64 PAX_CELL_SIZE = {32.0, 32.0};

/**
 * Half of a single cell in pixels.
 */
static const v2f64 PAX_CELL_HALF = PAX_CELL_SIZE / 2.0;

/**
 * Size of the view in tiles.
 */
static const v2f64 PAX_VIEW_SIZE = {43.0, 18.0};

/**
 * Half of the view in tiles.
 */
static const v2f64 PAX_VIEW_HALF = PAX_VIEW_SIZE / 2.0;

/**
 * Size of each grid in tiles.
 */
static const v2u64 PAX_GRID_SIZE = {50u, 20u};

/**
 * Total amount of actors in the game.
 */
static const u64 PAX_MAX_ACTORS = 10u;

#endif // DEMO_DEFINE_HPP
