Js.log "hello"; /* init var */

let polygon: Type.polygon = [{x: 0.0, y: 0.0}, {x: 2.0, y: 5.0}, {x: 10.0, y: 2.0}];

let setZones: list Type.polygon => unit = fun zones => Js.log zones;

/* component */
ReactDOMRe.renderToElementWithId
  <div> <DropZone setZones /> <Badge zones=[polygon] colors=["red"] /> </div> "app";
