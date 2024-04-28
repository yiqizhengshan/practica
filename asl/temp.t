function fact
  params
    _result integer array
    n integer array
  endparams

  vars
    f integer
  endvars

     %1 = 1
     f = %1
  label startwhile1 :
     %2 = 1
     %3 = n <= %2
     %3 = not %3
     ifFalse %3 goto endwhile1
     %4 = f * n
     f = %4
     %5 = 1
     %6 = n - %5
     n = %6
     goto startwhile1
  label endwhile1 :
     _result = f
     return
     return
endfunction

function main
  vars
    max integer
    i integer
    f integer
    end boolean
  endvars

     %1 = 0
     i = %1
     %2 = 1
     end = %2
     readi %3
     max = %3
     %4 = i <= max
     ifFalse %4 goto else1
     %5 = 0
     end = %5
     goto endif1
  label else1 :
     %6 = 0
     i = %6
  label endif1 :
  label startwhile1 :
     %7 = not end
     ifFalse %7 goto endwhile1
     writei i
     writes "!="
     pushparam 
     pushparam i
     call fact
     popparam 
     popparam %8
     writei %8
     writes "\n"
     %9 = i == max
     ifFalse %9 goto else2
     %10 = 1
     end = %10
     goto endif2
  label else2 :
     %11 = 1
     %12 = i + %11
     i = %12
  label endif2 :
     goto startwhile1
  label endwhile1 :
     return
endfunction


