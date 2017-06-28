external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame" [@@bs.val];

let style = Type.getClassName "app";


module App = {
  type state = {
    badge: Type.badge,
    lightSource: Type.point
  };

  let setZones paths state _self => {

    let zones = paths
      |> Illuminate.computeDefaultZones;

    ReasonReact.Update {...state, badge: {zones: zones}}
  };

  let setLightSource lightSource state _self => ReasonReact.Update {...state, lightSource};



  let handleMouseMove event state self => {
    let mouse: Type.point = {
      x: float_of_int (ReactEventRe.Mouse.clientX event),
      y: float_of_int (ReactEventRe.Mouse.clientY event)
    };
    setLightSource mouse state self
  };
  let rec loop t set => {
    let u = t + 1;
    let lightSource: Type.point = {
      x: 340.0 *. cos (float_of_int u /. 30.0),
      y: 340.0 *. sin (float_of_int u /. 30.0)
    };
    set lightSource;
    requestAnimationFrame (fun () => loop u set)
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

      Bs_fetch.fetch "elk.svg"
        |> Js.Promise.then_ Bs_fetch.Response.text
        |> Js.Promise.then_ (
          fun text => {
            text |> Parse.extractSvgPath |> (self.update setZones);
            Js.Promise.resolve ()
          }
        )
      |> ignore;

      loop 0 (self.update setLightSource);

      ReasonReact.NoUpdate
    },

    render: fun state self => {

      let {badge, lightSource} = state;

      let colors =
        List.map
          (fun zone => Illuminate.computeColor zone lightSource)
          badge.zones;

      let extractVertices : Type.zone => Type.polygon = fun zone => zone.vertices;

      let viewport = List.map extractVertices badge.zones |> List.flatten |> Point.boundingBox |> ( fun box => Point.expandBoundingBox box {x:160.0,y:160.0} );


      <div className=( style "container" )>
        <div className=( style "editor" )>
          <Canvas viewport>
            <Arrow b=lightSource a={x:0.0, y:0.0} />
            <Zones colors zones=(badge.zones) />
            <Normals zones=(badge.zones) />
            <LightSource lightSource />
          </Canvas>

          <DropZone setZones=(self.update setZones) />
        </div>
        <div className=( style "badge" )>
          <Badge lightSource zones=badge.zones />
        </div>
      </div>
    }
  };
};

/* component */
ReactDOMRe.renderToElementWithId <div> <App /> </div> "app";
