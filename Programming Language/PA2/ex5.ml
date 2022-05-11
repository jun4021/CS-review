let p li =
        Format.printf "[";
        List.iter (fun x -> Format.printf "%d " x) li;
        Format.printf "]\n";

in
let rec range first last =
        if first > last then []
        else
                if first = last then [first] else first  :: range (first+1) last

in 
Format.printf "range 10 15 => ";p (range 10 15);
Format.printf "range (-2) 7 => ";p (range (-2) 7);
Format.printf "range 9 3 => ";p (range 9 3);
Format.printf "range 22 22 => ";p (range 22 22);
Format.printf "range 55 (-12) => ";p (range 55 (-12));
