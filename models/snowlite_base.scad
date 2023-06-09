/**
 * Case Base
 */

// models
include <battery.scad>
include <ada_pcb571.scad>

// disable previews
battery_preview = false;
ada_pcb571_preview = false;

// base
snowlite_base_wall_thickness = 2;
snowlite_base_wall = 3; // outer wall thickness
snowlite_base_lip = 2; // inner lip thickness
snowlite_base_radius = 5; // used for curvature of case corners
snowlite_base_internal_components_height = ada_pcb571_height + battery_width + 6; // 
snowlite_base_clearance_depth = 28;

/**
 * Round rectangle shape.
 */
module rounded_square(width, length, radius) {
    hull() {
        translate([radius, radius, 0])
        circle(radius);
        
        translate([width - radius, radius, 0])
        circle(radius);
        
        translate([radius, length - radius, 0])
        circle(radius);
        
        translate([width - radius, length - radius, 0])
        circle(radius);
    }
}

/**
 * Base & PCB Mount Pins
 */
module base_mount_pins() {
    offset_width = 0.5 * (ada_pcb571_width - ada_pcb571_mount_width);
    offset_length = 0.5 * (ada_pcb571_length - ada_pcb571_mount_length);

    translate([
        offset_width,
        offset_length
    ])
    linear_extrude(3 * ada_pcb571_height) {
        offset(r=-0.4) {
            circle(ada_pcb571_mount_radius);
        }
    }
   
    translate([
        ada_pcb571_width - offset_width,
        offset_length
    ])
    linear_extrude(3 * ada_pcb571_height) {
        offset(r=-0.4) {
            circle(ada_pcb571_mount_radius);
        }
    }
}

/**
 * Base
 */
module snowlite_base() {
    union() {  
        union() {
            // pcb mount pins
            base_mount_pins();

            // lip
            translate([-14,  -40, 0]) {
                linear_extrude(2) {
                    rounded_square(110, 100, 5);
                }
            }

            // wall of case
            difference() {
                translate([-9, -35, 0]) {
                    linear_extrude(snowlite_base_clearance_depth) {
                        rounded_square(100,90,5);
                    }
                }

                translate([-7,-33,0]) {
                    linear_extrude(snowlite_base_clearance_depth + 10) {
                        rounded_square(96,86,6);
                    }
                }
            }

            // battery container
            difference() {
                translate([10, -35, 0]) {
                    linear_extrude(battery_length + 4) {
                        rounded_square(60, 34, 5);
                    }
                }

               // battery cable hole
               translate([12,-33,0]) {
                    linear_extrude(battery_length + 14) {
                        rounded_square(56, 30, 6);
                    }
                
                    translate([45, 25, 0]) {
                        cube(size = [10,10,battery_length + 14]);
                    }
                }  
            }       
        }                      
    }  
}

/**
 * Preview
 */
snowlite_base_preview = true;
if (snowlite_base_preview) {
    $fn = 64;
    snowlite_base();
}
