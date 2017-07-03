

type state = {
  dragged : bool,
};

module Normal = {

  let handleMouseMove setNormal event state self => {
    let mouse: Type.point = {
      x: float_of_int (ReactEventRe.Mouse.clientX event),
      y: float_of_int (ReactEventRe.Mouse.clientY event)
    };

    mouse |> Point.normalize |> setNormal;

    ReasonReact.NoUpdate
  };

  let handleMouseUp event state self => {
    ReasonReact.Update {...state, dragged:false}
  };

  let handleMouseDown setNormal self _event => {
    Common.startDrag ( self.ReasonReact.update ( handleMouseMove setNormal ) ) ( self.ReasonReact.update handleMouseUp );

    self.ReasonReact.update ( fun _ state self => ReasonReact.Update {...state, dragged:true} ) ();
  };

  let component = ReasonReact.statefulComponent "Normal";
  let make zone::(zone : Type.zone) setNormal::(setNormal :  Type.point => unit  ) _children => {
    ...component,

    initialState: fun () => {
      {dragged:false};
    },

    render: fun state self => {

      let r = state.dragged ? 60.0 : 40.0;

      let a = zone.center;
      let b = ( Point.scale zone.normal r ) |> Point.add a;

      <g onMouseDown=( handleMouseDown setNormal self )>
        <Arrow a b />
      </g>
    }
  };
};

let createNormal = fun setNormal i zone => {
    <Normal key=( string_of_int i ) zone setNormal=(setNormal i)   />;
  };

let component = ReasonReact.statelessComponent "Normals";

let make zones::(zones: list Type.zone) setNormal::(setNormal : int => Type.point => unit  ) _children => {
  ...component,
  render: fun () _self =>
    <g> (zones |> List.mapi ( createNormal setNormal ) |> Array.of_list |> ReasonReact.arrayToElement) </g>
};
