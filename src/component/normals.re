let createNormal: int => Type.zone => 'a =
  fun i zone => {
    let a = zone.center;
    let b = ( Point.scale zone.normal 40.0 ) |> Point.add a;

    <Arrow key=( string_of_int i ) a b />
  };

let component = ReasonReact.statelessComponent "Normals";

let make zones::(zones: list Type.zone) _children => {
  ...component,
  render: fun () _self =>
    <g> (zones |> List.mapi createNormal |> Array.of_list |> ReasonReact.arrayToElement) </g>
};
