(* --------------------------------------------------------------------------- *)
(* Ce fichier définit en OCAML des graphes sur lesquels tester des colorations *)

(* Trois graphes pour tester la coloration glouton *)

let g31 = [ 456,496 ; 456,536 ; 456,696 ; 456,776 ; 496,576 ; 496,656 ; 496,696 ; 496,736 ; 536,696 ; 536,736 ; 536,776 ; 576,776 ; 616,656 ; 616,696 ; 616,736 ; 616,776 ; 656,776 ; 696,736 ; 736,776 ; 816,856];;

let g32 = [ 456,496 ; 456,616 ; 456,656 ; 856,456 ; 496,536 ; 456,856 ; 496,696 ; 456,856 ; 536,576 ; 536,736 ; 576,616 ; 576,776 ; 616,816 ; 656,736 ; 856,456 ; 656,776 ; 696,776 ; 736,816 ; 456,856 ; 696,816];;

let g33 = [ 456,496 ; 456,736 ; 456,616 ; 456,656 ; 496,616 ; 496,536 ; 536,776 ; 536,576 ; 536,616 ; 576,616 ; 576,696 ; 616,656 ; 616,696 ; 656,696 ; 736,776 ; 736,816 ; 776,816 ; 616,856 ; 856,616 ; 696,816];;


let listeCoul = [ 35 ; 37 ; 26 ; 16 ; 38 ; 19 ; 36 ; 33 ; 9 ; 31 ; 34 ; 30 ; 14 ; 29 ; 8 ; 13 ; 11 ; 23 ; 17 ; 28 ; 18 ; 27 ; 2 ; 25 ; 1 ; 5 ; 20 ; 39 ; 40 ; 4 ; 21 ; 32 ; 6 ; 12 ; 1];;
(* --------------------------------------------------------------------------- *)