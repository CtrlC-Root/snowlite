/**
 * 9 Volt Battery
 */

// battery
battery_width = 25;
battery_length = 16;
battery_height = 47;

// connector
battery_connector_height = 4;

// clearance values
battery_total_height = battery_height + battery_connector_height;

/**
 * Battery
 */
module battery() {
    color("silver")
    cube([battery_width, battery_length, battery_height]);
}

/**
 * Preview
 */
battery_preview = true;
if (battery_preview) {
    battery();
}
