function f
  params
    _result boolean array
    a integer array
    f float array
  endparams

  vars
    x integer
    b boolean
    z integer
  endvars

     readi z
     writei a
     writes "\n"
     %1 = 88
     %3 = float %1
     %2 = %3 *. f
     %5 = float z
     %4 = %5 -. %2
     writef %4
     readi b
     readf f
     ifFalse b goto endif1
     writes "h\n\tl\\a"
     %6 = -. f
     %7 = -. %6
     %8 = -. %7
     writef %8
     writes "\n"
  label endif1 :
     %9 = 1
     _result = %9
     return
     return
endfunction

function fz
  params
    _result float array
    r integer array
    u float array
  endparams

  label startwhile1 :
     %1 = 0.01
     %3 = float r
     %2 = %3 <=. %1
     %2 = not %2
     ifFalse %2 goto endwhile1
     %4 = 1
     %5 = r - %4
     r = %5
     goto startwhile1
  label endwhile1 :
     %6 = 0
     %7 = r == %6
     ifFalse %7 goto endif1
     %8 = 55555
     %9 = 5
     %10 = - %9
     %11 = 4
     %12 = %10 / %11
     %13 = float %12
     pushparam %8
     pushparam %13
     pushparam 
     call f
     popparam 
     popparam 
     popparam 
  label endif1 :
     %14 = 3
     %15 = r + %14
     %17 = float %15
     %16 = %17 *. u
     _result = %16
     return
     return
endfunction

function main
  vars
    a integer
    q float
  endvars

   %1 = 1
   %2 = - %1
   %3 = float %2
   q = %3
   %4 = 3
   %5 = 4
   %6 = %4 + %5
   %7 = 4444
   %8 = 3
   %10 = float %8
   %9 = q +. %10
   pushparam 
   pushparam %7
   pushparam %9
   call fz
   popparam 
   popparam 
   popparam %11
   pushparam 
   pushparam %6
   pushparam %11
   call fz
   popparam 
   popparam 
   popparam %12
   q = %12
   %13 = 3.7
   %14 = q +. %13
   %15 = 4
   %17 = float %15
   %16 = %14 +. %17
   writef %16
   writes "\n"
   return
endfunction


