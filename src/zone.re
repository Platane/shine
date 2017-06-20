let component = ReasonReact.statelessComponent "Zone";

let polygonToSvgPath polygon => "M0 0 L10 0 L5 10z" /* let polygonToSvgPath: polygon => string = fun polygon => "000"; */;

let make ::polygon ::fill _children => {
  ...component,
  render: fun () _self => {
    let d = polygonToSvgPath polygon;
    <path d fill />
  }
};
