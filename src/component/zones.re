
let createZone: int => (Type.zone, string) => 'a =
  fun i (zone, color) =>
    <path key=(string_of_int i) d=zone.path fill=color />;

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
