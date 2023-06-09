
/**
 * Case Cover
 */

// modules
include <ada_pcb571.scad>
include <snowlite_base.scad>

// disable previews
ada_pcb571_preview = false;
snowlite_base_preview = false;


// button
snowlite_cover_button_radius = 12.7 / 2; // 0.5 in -> 12.7 mm

/**
 * Cover
 */
module snowlite_cover() {

    union() {
        
        difference() {
            
            translate([0,0,0]) {
                linear_extrude(snowlite_base_clearance_depth) {
                    rounded_square(110,100,5);
                }
            }      
            translate([4.8,4.8,-2]) {
                linear_extrude(snowlite_base_clearance_depth) {
                    rounded_square(100+0.4,90+0.4,5+0.4);
                }
            } 
            // deeper inset
            translate([5,5,snowlite_base_clearance_depth -1]) {
                linear_extrude(3) {
                    rounded_square(100, 60, 5);
                }
            } 
            translate([7,7,snowlite_base_clearance_depth -2]) {
                linear_extrude(3) {
                    rounded_square(96, 56, 5);
                }
            }
            // button
            translate([95,85,snowlite_base_clearance_depth -3]) {
                linear_extrude(5) {
                    circle(snowlite_cover_button_radius);
                }
            }
    
            // buzzer holes
            translate([10,90,snowlite_base_clearance_depth -3]) {
                linear_extrude(5) {
                    circle(1);
                }
            }
            translate([10,85,snowlite_base_clearance_depth -3]) {
                linear_extrude(5) {
                    circle(1);
                }
            }  
            translate([15,85,snowlite_base_clearance_depth -3]) {
                linear_extrude(5) {
                    circle(1);
                }
            }
            
            translate([15,90,snowlite_base_clearance_depth -3]) {
                linear_extrude(5) {
                    circle(1);
                }
            }
            translate([10,80,snowlite_base_clearance_depth -3]) {
                linear_extrude(5) {
                    circle(1);
                }
            }
            translate([15,80,snowlite_base_clearance_depth -3]) {
                linear_extrude(5) {
                    circle(1);
                 }
            }
        }
    }
}

/**
 * Preview
 */
snowlite_cover_preview = true;
if (snowlite_cover_preview) {
    $fn = 64;
    snowlite_cover();
}
