external getClassName : string => string => string = "window.getClassName" [@@bs.val];

external startDrag : ( ReactEventRe.Mouse.t => unit )  => ( ReactEventRe.Mouse.t => unit ) => unit = "window.startDrag" [@@bs.val];

let string_of_float: float => string =
  fun f => f < 0.0001 && f > (-0.0001) ? "0" : string_of_float f ^ "0";
