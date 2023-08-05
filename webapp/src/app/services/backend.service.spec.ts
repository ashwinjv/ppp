import { TestBed } from '@angular/core/testing';
import { BackEndService, ImageLoadResult } from './backend.service';
import { CrownChinPointPair } from '../model/datatypes';
import { Subscription } from 'rxjs';

let t1 = null;
function tic() {
  t1 = performance.now();
}
function toc() {
  const t2 = performance.now();
  return t2 - t1;
}

async function createFile(url: string, type: string = 'image/jpeg') {
  const idx = url.lastIndexOf('/');
  const filename = idx >= 0 ? url.substring(idx + 1) : url;
  const response = await fetch(url);
  const data = await response.blob();
  const metadata = { type };
  const file = new File([data], filename, metadata);
  return file;
}

let subs = new Array<Subscription>();

describe('BackEndServiceService', () => {
  let service: BackEndService;
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [BackEndService],
    });

    service = TestBed.get(BackEndService);
    expect(service).toBeTruthy();
  });

  afterEach(() => {
    for (let sub of subs) {
      sub.unsubscribe();
    }
    subs.length = 0;
  });

  it('should perform well', (done) => {
    expect(service).toBeTruthy();

    const measurements = new Map<string, number>();

    tic();
    let first = true;
    service.runtimeInitialized.subscribe(() => {
      measurements.set('WASM loaded and configured', toc());
      createFile('testdata/20190918_083809.jpg').then((imageFile) => {
        tic();
        service.imageLoaded.subscribe((imageLoadResult: ImageLoadResult) => {
          if (first) {
            expect(imageLoadResult).toBeNull();
            first = false;
            return;
          }
          measurements.set('Image loaded', toc());

          expect(imageLoadResult).toBeTruthy();
          expect(imageLoadResult.imgKey).toBeTruthy();
          tic();
          service.retrieveLandmarks(imageLoadResult.imgKey);
          let sub1 = service.landmarksUpdated.subscribe((landMarks: CrownChinPointPair) => {
            measurements.set('Landmarks retrieved', toc());
            sub1.unsubscribe();
            const lm = landMarks as CrownChinPointPair;
            expect(lm).toBeTruthy();
            measurements.forEach((value: number, key: string) => {
              console.log(`${key} => ${Math.round(value)}ms`);
            });
            done();
          });
        });
        service.loadImageInMemory(imageFile);
      });
    });
  }, 25000);
});
