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
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (vote_comment user_id comment_id (n, tl))))

(* Q 4.3 *)
let rec get_comment comment_id com_base = match (com_base : comments) with
  | (n, []) -> failwith "not found"
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if comment_id = c_id 
      then txt 
      else get_comment comment_id (n, tl)

(* Q 4.4 *)
let rec get_comments author_id com_base = match (com_base : comments) with
  | (n, []) -> []
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if author_id = u_id 
      then txt :: get_comments author_id (n, tl)
      else get_comments author_id (n, tl)


(* fnc that checks if voted for a comment in a com_base *)
let rec has_voted user_id u_id_l = match (u_id_l : user_id list) with
  | [] -> false
  | hd :: tl -> hd = user_id || has_voted user_id tl


(* Q 4.5 *)     
let rec get_voted_comments user_id com_base = match (com_base : comments) with
  | (n, []) -> []
  | (n, (c_id, u_id, txt, u_id_l) :: tl) ->
      if has_voted user_id u_id_l
      then txt :: get_voted_comments user_id (n, tl)
      else get_voted_comments user_id (n, tl)


(* Q 4.6 *)
(* when we remove an element, we do not update (fst comments)
  because it remembers the amount of comments created from the beginning
*)
let rec remove_comment comment_id (comments : comments) : comments = match comments with
  | (n, []) -> failwith "not found"
  | (n, (c_id, u_id, txt, u_id_l) :: tl) ->
      if comment_id = c_id 
      then (n, tl)
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (remove_comment comment_id (n, tl))))


(* Q 4.7 *)
let rec remove_comments user_id (comments : comments) : comments = match comments with
  | (n, []) -> (n, [])
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if user_id = u_id 
      then (n, snd (remove_comments user_id (n, tl)))
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (remove_comments user_id (n, tl))))


(* Q 4.8 *)
let rec update_comment user_id comment_id f comments : comments = match comments with
  | (n, []) -> failwith "not found"
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if (comment_id = c_id) && (user_id <> u_id)
      then failwith "author"
      else if (comment_id = c_id) && (user_id = u_id)
      then (n, (c_id, u_id, f txt, u_id_l) :: tl)
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (update_comment user_id comment_id f (n, tl))))


(* ma of 2 ints *)
let max a b = 
  if a >= b 
  then a
  else if a < b
  then b

(* Q 4.9 *)
let rec top_three comments = 
  let rec tr cl a1 a2 a3 = match cl with
    | (c_id, u_id, txt, u_id_l) -> true
  in
  tr snd comments 0 0 0


(* force int in comments fields:-user_id, bcs 'a accepts every type *)