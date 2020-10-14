(* Partie A - Fonctions et n-uplets *)
let e1 = ((6, true), 67)
         
let e2 = ((fun x -> x ), 'z')
      
         
let f1 x y = match x, y with 
  | 1, true -> (1, false)
  | _, _ -> (0, false)
    (*
let f1 x y = match x, y with
  | 1, true -> (0, false)
  | 0, false -> (1, true)
  | _, _ -> failwith "erreur"*)
              
let f2 a = true
  
let f3 a b = if a = b then 6 else 7
  
let f4 (a, b) = (b, a) 
  

let f5 = fun f -> fun g -> fun h -> fun i -> fun j -> h (g (fst (f i)) (snd (f j)) , true)
    
let f6 = fun f -> fun g -> fun h -> g h (f h)
    
let f7 (a, b, c) = b (c, a c)
  
let f8 a b c d = if (a = b) && (d = c) then (a, c) else (b, d)
(*
      let f8 a b c d = match a = b, b = a, c = d, d = c with
        | true, true, true, true -> (a, c)
        | _, _, _, _ -> failwith "not defined"
*) 

let cube e = e * e * e

let quad a = a * 4
             
let estPair n = n mod 2 = 0
                
let max3 a b c = max (max a b) c 
    
let discriminant a b c = b * b - 4 * a *c
                                 
let estImpair a = estPair a = false
                  
let choix x = match estPair x with 
  | true -> cube x
  | false -> quad x
               
let nbRac a b c =  
  let n = discriminant a b c in 
  if n > 0 then 2
  else if n = 0 then 1
  else 0
    
let xor a b = match a, b with
  | false, false -> false
  | false, true -> true
  | true, false -> true
  | true, true -> false
  
let nor a b = match a, b with
  | false, false -> true
  | false, true -> false
  | true, false -> false
  | true, true -> false
  
  
let nand a b = match a, b with
  | false, false -> true
  | false, true -> true
  | true, false -> true
  | true, true -> false
    
(* Partie B - Récursion *) 


let sommeChiffres n =
  let rec somme k = match k with
    | 0 -> 0
    | _ -> k mod 10 + somme (k / 10)
  in
  if n < 0 then failwith "valeurs negatives non permises"
  else somme n
      
      
let sommeIteree n =
  let rec somme k =
    let r = k mod 10
    in
    if k = 0 then 0
    else if r + somme(k / 10) >= 10 then r
    else r + somme (k/10) 
  in
  if n < 0 then failwith "valeurs negatives non permises"
  else somme n
      
      
let dernierCh n =
  let rec dCh k = 
    let i = k / 10 in
    if i = 0 then k
    else dCh i
  in if n = 0 then failwith "not null plz"
  else dCh n