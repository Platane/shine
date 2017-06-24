let component = ReasonReact.statelessComponent "Badge";

let createZonePaths = List.map2 (fun polygon fill => <Zone polygon fill />);

let make zones::(zones: list Type.polygon) colors::(colors: list string) _children => {
  ...component,
  render: fun () _self => {
    let box = Point.boundingBox (List.flatten zones);
    let viewBox =
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
    <svg viewBox>
      (ReasonReact.arrayToElement (Array.of_list (createZonePaths zones colors)))
    </svg>
  }
};
