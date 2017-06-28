
let style = Common.getClassName "canvas";

let makeViewBox: Type.box => string =
  fun box =>
    String.concat
      " "
      (
        List.map
          (fun s => s ^ "0")
          [
            string_of_float box.min.x,
            string_of_float box.min.y,
            string_of_float (box.max.x -. box.min.x),
            string_of_float (box.max.y -. box.min.y)
          ]
      );

let component = ReasonReact.statelessComponent "Canvas";
let make viewport::(viewport: Type.box) children => {
  ...component,
  render: fun () _self => {

    <svg className=( style "container" ) viewBox=(makeViewBox viewport)>
      ( ReasonReact.arrayToElement children )
    </svg>
  }
};