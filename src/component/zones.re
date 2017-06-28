

let createZone : Type.zone => string => 'a = fun zone color =>
  <path d = ( zone.path ) fill = color />;

let component = ReasonReact.statelessComponent "Zones";
let make zones::(zones: list Type.zone) colors::(colors: list string) _children => {
  ...component,
  render: fun () _self =>
    <g>
    (
        List.map2 createZone zones colors
          |> Array.of_list
          |> ReasonReact.arrayToElement
    )
  </g>
};
