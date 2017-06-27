module App = {
  type state = {
    badge: Type.badge,
    lightSource: Type.point
  };
  let setZones polygons state _self => {
    let zones = Illuminate.computeDefaultZones polygons;
    ReasonReact.Update {...state, badge: {zones: zones}}
  };
  let setLightSource lightSource state _self => {
    ReasonReact.Update {...state, lightSource}
  };
  let component = ReasonReact.statefulComponent "App";
  let make _children => {
    ...component,
    initialState: fun () => {
      let badge: Type.badge = {zones: []};
      let lightSource: Type.point = {x: 100.0, y: 10.0};
      {badge, lightSource}
    },
    didMount: fun _state self => {
      Bs_fetch.fetch "ball.svg" |> Js.Promise.then_ Bs_fetch.Response.text |>
      Js.Promise.then_ (
        fun text => {
          let polygons = Parse.svgToPolygons text;
          (self.update setZones) polygons;
          Js.Promise.resolve ()
        }
      ) |> ignore;
      ReasonReact.NoUpdate
    },
    render: fun state self => {
      let {badge, lightSource} = state;
      let colors = List.map (fun zone => Illuminate.computeColor zone lightSource) badge.zones;
      <div>
        <div />
        <DropZone setZones=(self.update setZones) />
        <Badge zones=badge.zones colors />
      </div>
    }
  };
};

/* component */
ReactDOMRe.renderToElementWithId <div> <App /> </div> "app";
