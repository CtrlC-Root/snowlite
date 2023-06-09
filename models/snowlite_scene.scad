/**
 * Snowlite Scene
 */
 
 module snowlite_scene() {
     
     union() {
         
         // tree
         difference() {
             
            translate([70,30,2])
            rotate_extrude($fn=10) {

            translate([-15,0,0])
                polygon(points = [[30,0], [35,5], [28,12], [32,16], [25,23], [28,26], 
                                  [21,33], [23,35], [19,39], [15,42], [15,0]], convexity = 1);
            }
            
            // cut-out for tree
            translate([63,21,-2])
            cube([15,18,22]); 
         }
         
        // ground
        difference() {
         
            cube(size = [100,60,2]);
         
            translate([12,20,-4])
            cube(size = [26,26,30]);
            
            translate([63,21,-2])
            cube([15,18,22]);
         
        }
        
        // house
        // translation of the first house
        translate([10,18,0])
        
        difference() {
         
         
            union() {

            // house body
            cube(size = [30,30,30]);
         
            // house roof
            translate([0,32,0]) {
                rotate([90,0,0]) {
                    linear_extrude(34) {
                        polygon(points = [[-4, 30], [15,40], [34,30]], convexity = 1);
                    }
                }
            }
        
            // house door
            translate([10,-0.5,0]) {
                cube(size = [10,0.5,10]);
            }
        }
         
         
         // house windows
        translate([2,-0.1,15]) {
            cube(size = [10,0.7,10]);
        }
        
        translate([18,-0.1,15]) {
            cube(size = [10,0.7,10]);
        }
        
        translate([2,2,-4])
        cube(size = [26,26,30]);
        
        } 
    } 
 }
 
 /**
 * Preview
 */
snowlite_scene_preview = true;
if (snowlite_scene_preview) {
    $fn = 64;
    snowlite_scene();
}