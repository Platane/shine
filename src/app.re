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
        zones: []
      };
      let lightSource: Type.point = {x: 0.0, y: 0.0};
      {badge, lightSource}
    },
    didMount: fun _state self => {
      Bs_fetch.fetch "ball.svg"
        |> Js.Promise.then_ Bs_fetch.Response.text
        |> Js.Promise.then_ (fun text => {
          let polygons = Parse.svgToPolygons text;
          (self.update setZones) polygons;
          Js.Promise.resolve ()
        })
        |> ignore;

      ReasonReact.NoUpdate
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
