#use "graphes.ml"

(* largeur *)
let rec largeur attente estBut etatsSuivants = match attente with
    []-> failwith "pas de but trouve"
    | x::reste -> 
        if (estBut x) then (print_string "file d'attente:";
        print_list_string attente;
        print_newline (); x)
        else (print_string "file d'attente:"; print_list_string attente; 
        print_newline ();
        largeur (reste @ (etatsSuivants x)) estBut etatsSuivants);;


(* profondeur *)
let rec profondeur attente estBut etatsSuivants = 
    match attente with
    []-> failwith "pas de but trouve"
    | x :: reste -> 
        if (estBut x) then (print_string "file d'attente:";
        print_list_string attente;
        print_newline (); x)
        else (
        print_string "file d'attente:"; print_list_string attente;
        print_newline ();
        profondeur ((etatsSuivants x) @ reste) estBut etatsSuivants)

(* A star *)
(* listes des triplets à insérer dans la file d'attente *)
let creerLesFils etat g_etat opPoss hEtat = 
    let rec aux l = match l with
        | [] -> []
        | (operateur, cout_op, fils) :: tl -> (fils, g_etat + cout_op, hEtat fils) :: (aux tl)
    in (aux (opPoss etat))
(* match etat with
    | [] -> []
    | (operateur, cout_op, fils) :: tl -> (fils, g_etat + cout_op, hEtat fils) :: (tl @ (creerLesFils fils g opPoss hEtat)) *)

    (* (nom_fils, g.pere + snd opPoss fils, hEtat ) (_, delta , _)) *)



let () = creerLesFils
    (* let found = (profondeur [initG3] estButG3 etatsSuivantsG3) in
    print_string "Sommet trouvé: ";
    print_endline found *)