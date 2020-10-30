let nom = "KUNZE" and prenom = "Tarek"

type comment_id = int
type user_id = int
type text = string
type comment = comment_id * user_id * text * (user_id list)
type comments = int * (comment list)
let score (_, _, _, list_votes) =
  let rec length l = match l with
    | [] -> 0
    | _ :: l -> 1 + length l
  in length list_votes;;

  

(* Q 3.1 *)
let rec add_once e l = match l with 
  | [] -> e :: []
  | hd :: tl -> if e = hd then failwith "already" else hd :: (add_once e tl)

(* Q 3.2 *)
let rec remove_if p l = match l with
  | [] -> []
  | hd :: tl -> if (p hd) = true then remove_if p tl else hd :: (remove_if p tl)


(* procédures auxiliaire *)
let fst (f, s) = f
let snd (f, s) = s
let thr (f, s, t) = t
let forth (f, s, t, fo) = fo

(* Q 4 *)
let init_comments = (0, [])

(* Q 4.1 *)
let add_comment author text com_base = 
  let rec ac c = match c with
    | [] -> ((fst com_base) + 1, author, text, []) :: []
    | hd :: tl -> hd :: (ac tl)
  in
  if text = "" then failwith "no comment"
  else
    (fst com_base + 1, ac (snd com_base))

(* Q 4.2 *)
let rec vote_comment user_id comment_id (com_base : comments) : comments = match com_base with
  | (n, []) -> failwith "no comment" 
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      let is_the_comment = (c_id = comment_id)
      in
      if (user_id = u_id) && is_the_comment
      then failwith "autovote"
      else
      if is_the_comment
      then (n, (c_id, u_id, txt, (add_once user_id u_id_l)) :: tl)
      else (fst com_base, (c_id, u_id, txt, u_id_l) :: (snd (vote_comment user_id comment_id (n, tl))))


(* Q 4.3 
let get_comment comment_id com_base = 
  let rec gc cl = match cl with
    | [] -> failwith "not found"
    | hd :: tl -> if comment_id = (snd hd) then (thr hd) else gc tl
  in
  gc (snd com_base)
*)

