let p l1 l2 l3=
        
        Format.printf "merge [";
        List.iter (fun x -> Format.printf "%d " x) l1;
        Format.printf "]";

        Format.printf "[";
        List.iter (fun x -> Format.printf "%d " x) l2;
        Format.printf "]";

        Format.printf" => ";

        Format.printf "[";
        List.iter (fun x -> Format.printf "%d " x) l3;
        Format.printf "]\n";
in    

let rec merge list1 list2 =
   match list1, list2 with
   | [], _ -> list2
   | _, [] -> list1
   | hd1 :: tl1, hd2 :: tl2 ->
   if hd1 > hd2 then hd1 :: merge tl1 list2 else hd2 :: merge list1 tl2

in
p [3;2;1] [5;4] (merge [3;2;1] [5;4]);
p [5;3] [5;2] (merge [5;3] [5;2]);
p [4;2] [] (merge [4;2] []);
p [] [2;1] (merge [] [2;1]);
p [] [] (merge [] []);
p [0;0;0;0] [0;0;0;0] (merge [0;0;0;0] [0;0;0;0]);
p [4;3;-2] [9;7;7] (merge [4;3;-2] [9;7;7]);
p [-2;-999] [] (merge [-2;-999] []);
