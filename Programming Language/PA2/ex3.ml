let sec_last intlist =
        if List.length intlist < 2 then 0
        else
               List.nth intlist (List.length intlist -2)
in
Format.printf "sec_last [1;2;3;4;5] => %d\n" (sec_last [1;2;3;4;5]);
Format.printf "sec_last [4;3;2;1] => %d\n" (sec_last [4;3;2;1]);
Format.printf "sec_last [] => %d\n"  (sec_last []);
Format.printf "sec_last [1] => %d\n" (sec_last [1]);
Format.printf "sec_last [1;2] => %d\n" (sec_last [1;2]);
