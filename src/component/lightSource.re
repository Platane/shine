let component = ReasonReact.statelessComponent "LightSource";

let make lightSource::(lightSource: Type.point) _children => {
  ...component,
  render: fun () _self =>
    <g>
      <circle cx=(string_of_float lightSource.x) cy=(string_of_float lightSource.y) r="5" />
    </g>
};
