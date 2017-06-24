let component = ReasonReact.statelessComponent "Zone";

let pointToString (point: Type.point) :string =>
  string_of_float point.x ^ "0 " ^ string_of_float point.y ^ "0";

let prefix p s => p ^ s;

let polygonToSvgPath polygon =>
  switch polygon {
  | [head, ...q] =>
    "M" ^
    pointToString head ^
    String.concat "" (List.map (fun s => pointToString s |> prefix "L") q) ^ "z"
  | [] => ""
  };

let make ::polygon ::fill _children => {
  ...component,
  render: fun () _self => {
    let d = polygonToSvgPath polygon;
    <path d fill />
  }
};
