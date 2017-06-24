Js.log "hello"; /* init var */

let setZones: list Type.polygon => unit = fun zones => Js.log zones;

let badge: Type.badge = {
  zones: [
    [{x: 0.0, y: 0.0}],
    [{x: 0.0, y: 0.0}, {x: 10.0, y: 0.0}, {x: 5.0, y: 4.0}],
    [{x: 0.0, y: 10.0}, {x: 10.0, y: 10.0}, {x: 5.0, y: 14.0}]
  ]
};

/* component */
ReactDOMRe.renderToElementWithId
  <div> <DropZone setZones /> <Badge zones=badge.zones colors=["red", "yellow", "blue"] /> </div>
  "app";
