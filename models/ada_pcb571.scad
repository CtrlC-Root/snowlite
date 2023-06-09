/**
 * Adafruit Prototyping Board (571 holes)
 * https://www.adafruit.com/product/571
 */

// pcb
ada_pcb571_width = 81;
ada_pcb571_length = 51;
ada_pcb571_height = 1.6;

// mount holes
ada_pcb571_mount_radius = 3.2 / 2;
ada_pcb571_mount_width = 73.66;
ada_pcb571_mount_length = 0;

// parts
ada_pcb571_parts_height = 25;

// clearance dimensions
ada_pcb571_total_height = ada_pcb571_height + ada_pcb571_parts_height;

/**
 * Mount Holes
 */
module ada_pcb571_mount_holes() {
    offset_width = 0.5 * (ada_pcb571_width - ada_pcb571_mount_width);
    offset_length = 0.5 * (ada_pcb571_length - ada_pcb571_mount_length);

    translate([
        offset_width,
        offset_length
    ])
    circle(ada_pcb571_mount_radius);

    translate([
        ada_pcb571_width - offset_width,
        offset_length
    ])
    circle(ada_pcb571_mount_radius);
}

/**
 * PCB
 */
module ada_pcb571(include_pins=$preview, show_parts=$preview) {
    // board
    color([0.8, 0.6, 0.45])
    linear_extrude(ada_pcb571_height) {
        difference() {
            // board
            square([ada_pcb571_width, ada_pcb571_length]);
            
            // mount holes
            ada_pcb571_mount_holes();
        }
    }
    
    // mounting pins
    if (include_pins) {
        ada_pcb571_mount_pins();
    }
    
    // clearance region for mounted parts
    if (show_parts) {
        color("gray", 0.25)
        translate([0, 0, ada_pcb571_height + 0.1])
        cube([
            ada_pcb571_width,
            ada_pcb571_length,
            ada_pcb571_parts_height - 0.1
        ]);
    }
}

/**
 * Mount Pins
 */
module ada_pcb571_mount_pins() {
    color("grey")
    linear_extrude(2.4 * ada_pcb571_height) {
        offset(r=-0.4) {
            ada_pcb571_mount_holes();
        }
    }
}

/**
 * Preview
 */
ada_pcb571_preview = true;
if (ada_pcb571_preview) {
    $fn = 64;
    ada_pcb571();
}
