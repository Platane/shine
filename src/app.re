external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame" [@@bs.val];

let style = Common.getClassName "app";


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

  let setNormal : ( int , Type.point ) => state => 'b => 'c = fun ( i, normal ) state _self => {

    let transform : ( int => Type.zone => Type.zone ) = fun j zone => j == i ? { ...zone, normal } : zone;

    let zones = List.mapi transform  state.badge.zones;

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
      x: 3040.0 *. cos (float_of_int u /. 30.0),
      y: 3040.0 *. sin (float_of_int u /. 30.0)
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

      Bs_fetch.fetch "ball.svg"
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

      let setNormal_ : int => Type.point => unit = fun i point => ( self.update setNormal )( i, point );

      <div className=( style "container" )>
        <div className=( style "editor" )>
          <BadgeEditor zones=state.badge.zones lightSource=state.lightSource setNormal=setNormal_ />
        </div>
        <div className=( style "badge" )>
          <Badge zones=state.badge.zones lightSource=state.lightSource  />
        </div>
        <DropZone setZones=(self.update setZones) />
      </div>
    }
  };
};

/* component */
ReactDOMRe.renderToElementWithId <div> <App /> </div> "app";
