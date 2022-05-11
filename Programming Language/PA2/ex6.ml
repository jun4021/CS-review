let rec sigma (a, b,f) =
        if a>b then 0
        else
                if a=b then f a
                else f a + sigma ((a+1), b, f)
in

Format.printf "sigma(10,10,(fun x->x)) => %d\n" (sigma(10,10,(fun x->x)));
Format.printf "sigma(11,10,(fun x->x)) => %d\n" (sigma(11,10,(fun x->x)));
Format.printf "sigma(10,5,(fun x->x)) => %d\n" (sigma(10,5,(fun x->x)));
Format.printf "sigma(1,10,(fun x->if x mod 2 = 0 then 1 else 0)) => %d\n" (sigma(1,10,(fun x->if x mod 2 = 0 then 1 else 0)));
Format.printf "sigma(2,10,(fun x->x+10)) => %d\n" (sigma(2,10,(fun x->x+10)));
Format.printf "sigma(0,100,(fun x->0)) => %d\n" (sigma(0,100,(fun x->0)));
Format.printf "sigma(10,12,(fun x->2*x)) => %d\n" (sigma(10,12,(fun x->2*x)));
