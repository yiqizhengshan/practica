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
     ifFalse %4 goto endif1
     %5 = 0
     end = %5
  label endif1 :
  label startwhile1 :
     %6 = not end
     ifFalse %6 goto endwhile1
     writei i
     writes "!="
     pushparam 
     pushparam i
     call fact
     popparam 
     popparam %7
     writei %7
     writes "\n"
     %8 = i == max
     ifFalse %8 goto endif2
     %9 = 1
     end = %9
  label endif2 :
     goto startwhile1
  label endwhile1 :
     return
endfunction


