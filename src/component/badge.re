let style = Common.getClassName "badge";

let component = ReasonReact.statelessComponent "Badge";

let make zones::(zones: list Type.zone) lightSource::(lightSource: Type.point) _children => {
  ...component,
  render: fun () _self => {

    let colors = List.map (fun zone => Illuminate.computeColor zone lightSource) zones;

    let extractVertices: Type.zone => Type.polygon = fun zone => zone.vertices;

    let viewport = List.map extractVertices zones |> List.flatten |> Point.boundingBox;

    <div className=(style "container")>
      <Canvas viewport>
        <Zones colors zones />
      </Canvas>
    </div>
  }
};
