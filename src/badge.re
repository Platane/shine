let component = ReasonReact.statelessComponent "Badge";

let createZonePaths = List.map2 (fun polygon fill => <Zone polygon fill />);

let make zones::(zones: list Type.polygon) colors::(colors: list string) _children => {
  ...component,
  render: fun () _self =>
    <svg viewBox="0 0 100 100">
      (ReasonReact.arrayToElement (Array.of_list (createZonePaths zones colors)))
    </svg>
};
