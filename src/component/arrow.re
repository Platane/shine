open Point;
open Illuminate;

let pointToString (point: Type.point) :string =>
  string_of_float2 point.x ^ " " ^ string_of_float2 point.y ;

let head = 10.0;
let width = 4.0;


let component = ReasonReact.statelessComponent "Arrow";

let make a::(a: Type.point) b::(b: Type.point) _children => {
  ...component,
  render: fun () _self => {

    let v = sub b a |> normalize;

    let d =
      String.concat
        " "
        [
          "M",
          pointToString a,
          "L",
          string_of_float2 (b.x -. v.x *. head ),
          string_of_float2 (b.y -. v.y *. head ),
          "z",
          "M",
          pointToString b,
          "L",
          string_of_float2 (b.x -. v.x *. head +. v.y *. width),
          string_of_float2 (b.y -. v.y *. head -. v.x *. width),
          "L",
          string_of_float2 (b.x -. v.x *. head -. v.y *. width),
          string_of_float2 (b.y -. v.y *. head +. v.x *. width),
          "z"
        ];

    <path d stroke="#888" fill="#888" />
  }
};
