Js.log "hello";

/* types */
type point = {
  x: float,
  y: float
};

type polygon = list point;

type badge = {zones: list polygon};

/* init var */
let polygon = [
  {x: 0.0, y: 0.0},
  {x: 2.0, y: 5.0},
  {x: 10.0, y: 2.0}
]; /* ReactDOMRe.renderToElementWithId <div /> "app"; */

/* component */
ReactDOMRe.renderToElementWithId <Badge zones=[polygon] colors=["red"] /> "app";
