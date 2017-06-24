let setZones: list Type.polygon => unit = fun zones => Js.log zones;

module App = {
  type state = {
    badge: Type.badge,
    lightSource: Type.point
  };
  let setZones polygons state _self => ReasonReact.Update {...state, badge: {zones: polygons}};
  let component = ReasonReact.statefulComponent "App";
  let make _children => {
    ...component,
    initialState: fun () => {
      let badge: Type.badge = {
        zones: [
          [{x: 0.0, y: 0.0}, {x: 10.0, y: 0.0}, {x: 5.0, y: 4.0}],
          [{x: 0.0, y: 10.0}, {x: 10.0, y: 10.0}, {x: 5.0, y: 14.0}]
        ]
      };
      let lightSource: Type.point = {x: 0.0, y: 0.0};
      {badge, lightSource}
    },
    render: fun state self => {
      let {badge, lightSource} = state;
      let colors = Illuminate.computeColors (badge, lightSource);
      <div> <DropZone setZones=(self.update setZones) /> <Badge zones=badge.zones colors /> </div>
    }
  };
};

/* component */
ReactDOMRe.renderToElementWithId <div> <App /> </div> "app";
