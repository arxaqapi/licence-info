
(* ================================== *)

(* Un petit graphe en extension : *)

let g1 = ["WA","NA" ; "WA","SA" ; "NA","SA" ; "NA","Q" ; "SA","Q" ; "SA","V" ; "SA","NSW" ; "Q","NSW" ; "NSW","V" ]

let g2 = ["A","B" ; "A","E" ; "B","C" ; "B","D" ; "B","E" ; "C","D" ; "D","E"]

let g7 = [("h","a");("h","d");("h","g");("b","c");("b","e");("b","f");("b","a");("c","f");("d","e");("d","a");("d","g");("e","g");("f","i")]

(* ================================== *)

(* Checks if two vertices s1 and s2 are adjacent *)
let sont_adjacents (g : ('a * 'a) list) (s1 : 'a) (s2 : 'a) : bool = 
  List.exists (fun (is1, is2) -> ((is1 = s1) && (is2 = s2)) || ((is1 = s2) && (is2 = s1))) g

(* Creates the list of the graphs vertices *)
let liste_sommets g =
  let la, lb = List.split g in 
  List.sort_uniq (fun a b -> if a = b then 0 else if a < b then -1 else 1) (la @ lb)

(* Creates the list of all adjacent vertices of a given vertice *)
let sommets_adjacents g s = 
  let rec aux lst = match lst with
  | [], [] -> []
  | h1 :: tl1, h2 :: tl2 -> 
    if h1 = s then h2 :: (aux (tl1, tl2)) else 
    if h2 = s then h1 :: (aux (tl1, tl2)) else (aux (tl1, tl2))
  | _, _ -> failwith "List sizes does not match"
  in List.sort_uniq (fun a b -> if a = b then 0 else if a < b then -1 else 1) (aux (List.split g))

(* === UTIL === *)

let next_color l = 
  let il = List.sort (fun a b -> if a = b then 0 else if a < b then -1 else 1) l in
  let rec aux l e = match l with
    | [] -> e
    | hd :: tl -> if hd = e then aux tl (e + 1) else e
  in aux il 1

let couleurs_utilisees coloration_partielle s_adjacents = 
  let rec aux col_partielle = match col_partielle with
  | [] -> []
  | (sommet, couleur) :: tl -> 
    if List.mem sommet s_adjacents = true 
    then couleur :: (aux tl)
    else aux tl
  in List.sort_uniq (fun a b -> if a = b then 0 else if a < b then -1 else 1) (aux coloration_partielle)


(* === UTIL === *)

(* Algo glouton sans heuristique, ordre de coloriage des sommets indifférents *)
let gloutonSansH g = 
  let sommets = liste_sommets g in
  let rec glout l_sommets colo_partielle = match l_sommets with
    | [] -> colo_partielle
    | s :: tl ->
      let v = couleurs_utilisees colo_partielle (sommets_adjacents g s) in
      let c = next_color v in 
      glout tl ((s, c) :: colo_partielle)
  in 
  let coloration_partielle = glout sommets [] in
  let cmax = List.fold_left (fun b e -> max b e) 0 (snd (List.split coloration_partielle)) 
  in coloration_partielle, cmax, sommets

(* Algo glouton avec heuristique statique, coloration par ordre de degré décroissant puis alpha *)
let gloutonDeg g = 
  let _, sommets = 
    List.split 
      (List.sort 
        (fun (voisins_a, sommet_a) (voisins_b, sommet_b) -> 
          if voisins_a = voisins_b 
          then 
            if sommet_a = sommet_b 
            then 0 
            else 
              if sommet_a < sommet_b 
              then -1 
              else 1 
          else 
            if voisins_a < voisins_b 
            then -1 
            else 1) 
        (List.map (fun sommet -> List.length (sommets_adjacents g sommet), sommet) (liste_sommets g)))
    in
    let rec glout l_sommets colo_partielle = match l_sommets with
    | [] -> colo_partielle
    | s :: tl ->
      let v = couleurs_utilisees colo_partielle (sommets_adjacents g s) in
      let c = next_color v in 
      glout tl ((s, c) :: colo_partielle)
  in 
  let coloration_partielle = glout sommets [] in
  let cmax = List.fold_left (fun b e -> max b e) 0 (snd (List.split coloration_partielle)) 
  in coloration_partielle, cmax, sommets
(*
- on recupère liste_sommets, on calcule pour chaque sommet sont nb degré sortant 
  et on recrée un liste qu'on trie de cette façon (List.sort (fun (a1, a2) (b1, b2) -> ))
- puis algo déroule sans prob
*)


(* let () =
  if sont_adjacents g1 "SA" "V" 
  then print_endline "Found adjacent nodes"
  else print_endline "Did not found adjacent nodes" *)
(* let () = gloutonSansH g1 *)