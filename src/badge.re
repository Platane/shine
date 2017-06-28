let component = ReasonReact.statelessComponent "Badge";

let createZonePaths = List.map2 (fun polygon fill => <Zone polygon fill />);

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

let make zones::(zones: list Type.zone) colors::(colors: list string) _children => {
  ...component,
  render: fun () _self => {

    let extractVertices : Type.zone => Type.polygon = fun zone => zone.vertices;

    let polygons = List.map extractVertices zones;

    let box = polygons |> List.flatten |> Point.boundingBox;

    <svg viewBox=(makeViewBox box)>
      (ReasonReact.arrayToElement (Array.of_list (createZonePaths polygons colors)))
    </svg>
  }
};
