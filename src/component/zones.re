let string_of_float = Common.string_of_float;

let string_of_point : Type.point => string = fun p => ( string_of_float p.x ) ^ " " ^ ( string_of_float p.y );

let prefix p s => p ^ s;

let polygonToSvgPath : Type.polygon => string = fun polygon =>
  switch polygon {
  | [head, ...q] =>
    [
      [
        "M",
        string_of_point head,
      ],
        q
        |> List.map (fun p =>
          "L" ^ string_of_point p
        )
    ]
    |> List.flatten
    |> String.concat " "

  | [] => ""
};


let createZone: int => (Type.zone, string) => 'a =
  fun i (zone, color) =>
    <path key=(string_of_int i) d=(polygonToSvgPath zone.vertices) fill=color />;

let component = ReasonReact.statelessComponent "Zones";

let make zones::(zones: list Type.zone) colors::(colors: list string) _children => {
  ...component,
  render: fun () _self =>
    <g>
      (
        List.map2 (fun a b => (a, b)) zones colors
          |> List.mapi createZone
          |> Array.of_list
          |> ReasonReact.arrayToElement
      )
    </g>
};
