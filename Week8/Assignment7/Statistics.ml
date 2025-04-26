let mean lst =
  let total = List.fold_left (+) 0 lst in
  float_of_int total /. float_of_int (List.length lst)

let median lst =
  let sorted = List.sort compare lst in
  let n = List.length sorted in
  if n mod 2 = 1 then
    float_of_int (List.nth sorted (n / 2))
  else
    let mid1 = List.nth sorted (n / 2 - 1) in
    let mid2 = List.nth sorted (n / 2) in
    float_of_int (mid1 + mid2) /. 2.0

let mode lst =
  let sorted = List.sort compare lst in
  let rec find_mode lst current count max_val max_count =
    match lst with
    | [] -> max_val
    | h::t ->
      let new_count = if h = current then count + 1 else 1 in
      let (new_max_val, new_max_count) =
        if new_count > max_count then (h, new_count) else (max_val, max_count)
      in
      find_mode t h new_count new_max_val new_max_count
  in
  match sorted with
  | [] -> failwith "Empty list"
  | h::t -> find_mode t h 1 h 1

let () =
  let lst = [1; 2; 2; 3; 4; 5; 8] in
  Printf.printf "Mean: %.2f\n" (mean lst);
  Printf.printf "Median: %.2f\n" (median lst);
  Printf.printf "Mode: %d\n" (mode lst)
