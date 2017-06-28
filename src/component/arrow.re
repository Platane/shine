open Point;
let string_of_float = Common.string_of_float;

let pointToString (point: Type.point) :string =>
  string_of_float point.x ^ " " ^ string_of_float point.y ;

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
          string_of_float (b.x -. v.x *. head ),
          string_of_float (b.y -. v.y *. head ),
          "z",
          "M",
          pointToString b,
          "L",
          string_of_float (b.x -. v.x *. head +. v.y *. width),
          string_of_float (b.y -. v.y *. head -. v.x *. width),
          "L",
          string_of_float (b.x -. v.x *. head -. v.y *. width),
          string_of_float (b.y -. v.y *. head +. v.x *. width),
          "z"
        ];

    <path d stroke="#888" fill="#888" />
  }
};
